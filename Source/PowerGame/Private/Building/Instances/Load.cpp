#include "Building/Instances/Load.h"

#include "Power/PowerNetwork.h"

void ALoad::EndPlay(const EEndPlayReason::Type reason) {

	Super::EndPlay(reason);

	if (m_network == nullptr) return;

	m_network->DisconnectLoad(this);
	m_network = nullptr;

}

void ALoad::Update(float supplyRatio) {

	m_suppliedPower = demand * supplyRatio;

}