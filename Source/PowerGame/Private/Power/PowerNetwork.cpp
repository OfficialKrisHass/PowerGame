#include "Power/PowerNetwork.h"

#include "Building/Instances/Generator.h"
#include "Building/Instances/Load.h"
#include "Building/Instances/Wire.h"

DEFINE_LOG_CATEGORY(LogPower);

APowerNetwork::APowerNetwork() {

	PrimaryActorTick.bCanEverTick = false;

}

void APowerNetwork::ConnectGenerator(AGenerator* generator) {

	PW_ASSERT(generator != nullptr, LogPower, TEXT("Can't connect invalid generator to power network '%s'."), *GetNameSafe(this));
	m_generators.Add(generator);

}
void APowerNetwork::ConnectLoad(ALoad* load) {

	PW_ASSERT(load != nullptr, LogPower, TEXT("Can't connect invalid load to power network '%s'."), *GetNameSafe(this));
	m_loads.Add(load);

}

APowerNetwork* APowerNetwork::HandleConnection(ABuildInstance* buildInstanceA, ABuildInstance* buildInstanceB, AWire* wire) {

	PW_ASSERT(buildInstanceA != nullptr && buildInstanceB != nullptr, LogPower, TEXT("Can't handle connection between invalid build instances."));

	APowerNetwork* networkA = buildInstanceA->m_powerNetwork;
	APowerNetwork* networkB = buildInstanceB->m_powerNetwork;

	APowerNetwork* resultingNetwork = nullptr;
	if (networkA != nullptr && networkB != nullptr) {

		if (networkA == networkB) {

			networkA->m_connections.Add(wire);
			return networkA;

		}

		// Case 1: 2 separete networks merging into one.
		// TODO: Implement proper merging (changing values, handling load, etc)

		APowerNetwork* oldNetwork = nullptr;
		if (networkA->m_connections.Num() >= networkB->m_connections.Num()) {

			resultingNetwork = networkA;
			oldNetwork = networkB;

		} else {

			resultingNetwork = networkB;
			oldNetwork = networkA;

		}

		// Reassign all buildings in the smaller network to the new one.
		// There will be repeated assignements, but in the end those are faster than to
		// check if the network was already assigned each and every time.

		for (TObjectPtr<AWire> connection : oldNetwork->m_connections) {

			connection->m_powerNetwork = resultingNetwork;
			connection->m_startBuildInstance->m_powerNetwork = resultingNetwork;
			connection->m_endBuildInstance->m_powerNetwork = resultingNetwork;

			resultingNetwork->AddBuildInstance(connection->m_startBuildInstance);
			resultingNetwork->AddBuildInstance(connection->m_endBuildInstance);
			resultingNetwork->m_connections.Add(connection);

		}

		// Finally, destroy the old network

		oldNetwork->Destroy();

	} else if (networkA == nullptr && networkB == nullptr) {

		// Case 2: 2 unconnected buildings, new network is created.

		resultingNetwork = buildInstanceA->GetWorld()->SpawnActor<APowerNetwork>();
		PW_ASSERT(resultingNetwork != nullptr, LogPower, TEXT("Could not spawn new power network."));

	} else
		// Case 3: 1 connected, 1 unconnected building, the existing network is used.
		resultingNetwork = networkA != nullptr ? networkA : networkB;

	buildInstanceA->m_powerNetwork = resultingNetwork;
	buildInstanceB->m_powerNetwork = resultingNetwork;

	resultingNetwork->AddBuildInstance(buildInstanceA);
	resultingNetwork->AddBuildInstance(buildInstanceB);

	resultingNetwork->m_connections.Add(wire);

	return resultingNetwork;

}

void APowerNetwork::AddBuildInstance(ABuildInstance* buildInstance) {

	if (AGenerator* generator = Cast<AGenerator>(buildInstance))
		m_generators.Add(generator);
	else if (ALoad* load = Cast<ALoad>(buildInstance))
		m_loads.Add(load);

}