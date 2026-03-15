#include "Building/Instances/Wire.h"

#include "Power/PowerNetwork.h"

void AWire::SetStartAndEnd(const FVector& startLocation, const FVector& endLocation) {

	Super::SetStartAndEnd(startLocation, endLocation);

}

void AWire::Connect(ABuildInstance* startBuildInstance, ABuildInstance* endBuildInstance) {

	m_startBuildInstance = startBuildInstance;
	m_endBuildInstance = endBuildInstance;

	m_powerNetwork = APowerNetwork::HandleConnection(startBuildInstance, endBuildInstance, this);

	startBuildInstance->ConnectWire(this);
	endBuildInstance->ConnectWire(this);

}