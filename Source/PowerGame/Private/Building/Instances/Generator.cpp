#include "Building/Instances/Generator.h"

#include "Power/PowerNetwork.h"

#include "PowerGameMode.h"

void AGenerator::BeginPlay() {

	Super::BeginPlay();

	//

}
void AGenerator::EndPlay(const EEndPlayReason::Type reason) {

	Super::EndPlay(reason);

	if (m_network == nullptr) return;

	m_network->DisconnectGenerator(this);
	m_network = nullptr;

}

void AGenerator::Respond(float freqError) {

	m_currentOutput = maxOutput * FMath::Clamp(1 + freqError * responseStrength, 0.0f, 1.0f);

}