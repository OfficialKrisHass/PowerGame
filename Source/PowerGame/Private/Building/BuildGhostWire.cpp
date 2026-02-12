#include "Building/BuildGhostWire.h"
#include "Building/BuildInstance.h"
#include "Building/Build.h"

#include "Building/ConstructionModeManager.h"

#include "Building/Instances/Wire.h"

void ABuildGhostWire::SetBuild(UBuild* build) {

	Super::SetBuild(build);

	// TODO: I don't like this :c
	SetActorHiddenInGame(true);

}

void ABuildGhostWire::Update(const FVector& hitLocation, ABuildInstance* hitBuildInstance) {

	// Handle snapping to poles and buildings

}

void ABuildGhostWire::Confirm(const FVector& location) {

	switch (m_state) {

	case EBuildGhostState::Preview: {

		m_startLocation = location;
		m_state = EBuildGhostState::StartSelected;

		break;

	}
	case EBuildGhostState::StartSelected: {

		PW_ASSERT(m_build->buildInstanceClass != nullptr, LogBuilding, TEXT("Can't confirm build with invalid Build Instance class. Build: '%s'"), *GetNameSafe(m_build));

		AWire* wireInstance = GetWorld()->SpawnActor<AWire>(m_build->buildInstanceClass, m_startLocation, GetActorRotation());
		PW_ASSERT(wireInstance != nullptr, LogBuilding, TEXT("Could not spawn actor of type ABuildInstance."));

		wireInstance->SetBuild(m_build);
		wireInstance->SetStartAndEnd(m_startLocation, location);

		// Reset back to preview for the next wire

		m_state = EBuildGhostState::Preview;

		break;

	}
	default: break;

	}

}