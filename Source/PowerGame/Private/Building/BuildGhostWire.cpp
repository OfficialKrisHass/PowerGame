#include "Building/BuildGhostWire.h"
#include "Building/Build.h"

#include "Building/ConstructionModeManager.h"

#include "Building/Instances/SplineBuildInstance.h"

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

		ASplineBuildInstance* splineInstance = GetWorld()->SpawnActor<ASplineBuildInstance>(m_build->buildInstanceClass, m_startLocation, GetActorRotation());
		PW_ASSERT(splineInstance != nullptr, LogBuilding, TEXT("Could not spawn actor of type ABuildInstance."));

		splineInstance->SetBuild(m_build);
		splineInstance->SetStartAndEnd(m_startLocation, location);

		// Reset back to preview for the next wire

		m_state = EBuildGhostState::Preview;

		break;

	}
	default: break;

	}

}