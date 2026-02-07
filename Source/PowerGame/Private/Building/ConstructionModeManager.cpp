#include "Building/ConstructionModeManager.h"

#include "Building/BuildGhost.h"
#include "Building/BuildInstance.h"

#include "Player/MainPlayerCharacter.h"
#include "Player/MainPlayerController.h"

#include <Camera/CameraComponent.h>

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputAction.h>

DEFINE_LOG_CATEGORY(LogBuilding);

UConstructionModeManager::UConstructionModeManager() {
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UConstructionModeManager::SelectBuildTool() {

	if (tool == EConstructionTool::BuildTool) {

		ExitConstructionMode();
		return;

	}
	
	PW_LOG(LogBuilding, TEXT("Selecting build tool."));

	// First deselect the deconstruct tool if selected

	if (tool == EConstructionTool::DeconstructTool) {

		if (highlightedBuildInstance != nullptr) {

			PW_LOG(LogBuilding, TEXT("Deselecting deconstruct tool."));

			highlightedBuildInstance->ResetHighlightMaterial();
			highlightedBuildInstance = nullptr;

		}

	} else // If deconstruct tool was selected, it added the IMC already.
		m_controller->AddMappingContext(constructionModeIMC);

	// Then do the actual selecting

	tool = EConstructionTool::BuildTool;

	m_buildGhost->SetActorHiddenInGame(false);
	m_buildGhost->SetBuild(testBuild);

}
void UConstructionModeManager::SelectDeconstructTool() {

	if (tool == EConstructionTool::DeconstructTool) {

		ExitConstructionMode();
		return;

	}

	PW_LOG(LogBuilding, TEXT("Selecting deconstruct tool."));

	// First deselect the build tool if selected

	if (tool == EConstructionTool::BuildTool)
		m_buildGhost->SetActorHiddenInGame(true);
	else // If build tool was selected prior, it added the IMC already.
		m_controller->AddMappingContext(constructionModeIMC);
	
	// Then do the actual selecting

	tool = EConstructionTool::DeconstructTool;

}

void UConstructionModeManager::ExitConstructionMode() {

	PW_LOG(LogBuilding, TEXT("Exiting construction mode."));

	switch (tool) {

	case EConstructionTool::BuildTool: m_buildGhost->SetActorHiddenInGame(true); break;
	case EConstructionTool::DeconstructTool: {

		if (highlightedBuildInstance == nullptr) break;

		highlightedBuildInstance->ResetHighlightMaterial();
		highlightedBuildInstance = nullptr;

		break;

	}
	default: return;

	}

	m_controller->RemoveMappingContext(constructionModeIMC);
	tool = EConstructionTool::None;

}

void UConstructionModeManager::BeginPlay() {

	Super::BeginPlay();

	m_character = Cast<AMainPlayerCharacter>(GetOwner());
	PW_ASSERT(m_character != nullptr, LogBuilding, TEXT("Build Mode Manager must be attached to actor of type AMainPlayerCharacter."));

	m_camera = m_character->GetCamera();
	PW_ASSERT(m_camera != nullptr, LogBuilding, TEXT("Could not retrieve UCameraComponent from '%s'."), *GetNameSafe(m_character));

	// Setup input

	m_controller = Cast<AMainPlayerController>(m_character->Controller);
	PW_ASSERT(m_controller != nullptr, LogBuilding, TEXT("Could not cast controller of '%s' to AMainPlayerController."), *GetNameSafe(m_character));
	PW_ASSERT(constructionModeIMC != nullptr, LogBuilding, TEXT("No Build mode IMC assigned to the Build Mode Manager "));

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(m_character->InputComponent);
	PW_ASSERT(inputComponent != nullptr, LogBuilding, TEXT("Could not retrieve UEnhancedInputComponent from '%s'."), *GetNameSafe(m_character));

	inputComponent->BindAction(confirmAction, ETriggerEvent::Started, this, &UConstructionModeManager::Confirm);

	inputComponent->BindAction(toggleGridSnapAction, ETriggerEvent::Started, this, &UConstructionModeManager::ToggleGridSnap);

	inputComponent->BindAction(exitAction, ETriggerEvent::Started, this, &UConstructionModeManager::ExitConstructionMode);

	// Setup build ghost

	SpawnBuildGhost();

}

void UConstructionModeManager::SpawnBuildGhost() {

	PW_ASSERT(buildGhostClass != nullptr, LogBuilding, TEXT("Can't spawn Build Ghost actor when no Build Ghost class is set in BuildModeManager."));

	FActorSpawnParameters params;
	params.Owner = GetOwner();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_buildGhost = GetWorld()->SpawnActor<ABuildGhost>(buildGhostClass, FTransform::Identity, params);
	PW_ASSERT(m_buildGhost != nullptr, LogBuilding, TEXT("Could not spawn Build Ghost actor."));

	m_buildGhost->SetActorHiddenInGame(true);

}

void UConstructionModeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (tool) {

	case EConstructionTool::BuildTool: HandleBuildTool(); break;
	case EConstructionTool::DeconstructTool: HandleDeconstructTool(); break;
	default: break;

	}

}

void UConstructionModeManager::HandleBuildTool() {

	FHitResult hit = FHitResult(EForceInit::ForceInit);
	FVector start = m_camera->GetComponentLocation();
	FVector end = start + (m_camera->GetForwardVector() * buildGhostRange);

	FCollisionQueryParams params = FCollisionQueryParams(TEXT("Build ghost params"), true, m_character);
	params.AddIgnoredActor(m_buildGhost);
	params.bReturnPhysicalMaterial = false;
	params.bDebugQuery = true;

	if (!GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params)) {

		if (!m_buildGhost->IsHidden())
			m_buildGhost->SetActorHiddenInGame(true);

		return;

	}
	if (m_buildGhost->IsHidden())
		m_buildGhost->SetActorHiddenInGame(false);

	FVector location = hit.ImpactPoint;
	if (gridSnap) {

		location.X = FMath::RoundToInt(location.X / gridSize) * gridSize;
		location.Y = FMath::RoundToInt(location.Y / gridSize) * gridSize;

	}

	m_buildGhost->SetActorLocation(location);

}
void UConstructionModeManager::HandleDeconstructTool() {

	FHitResult hit = FHitResult(EForceInit::ForceInit);
	FVector start = m_camera->GetComponentLocation();
	FVector end = start + (m_camera->GetForwardVector() * buildGhostRange);

	FCollisionQueryParams params = FCollisionQueryParams(TEXT("Deconstruct mode params"), true, m_character);
	params.AddIgnoredActor(m_buildGhost);
	params.bReturnPhysicalMaterial = false;
	params.bDebugQuery = true;

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params) && Cast<ABuildInstance>(hit.GetActor()) != nullptr) {

		ABuildInstance* buildInstance = Cast<ABuildInstance>(hit.GetActor());
		if (highlightedBuildInstance != nullptr && highlightedBuildInstance != buildInstance)
			highlightedBuildInstance->ResetHighlightMaterial();

		highlightedBuildInstance = buildInstance;
		highlightedBuildInstance->SetHighlightMaterial(deconstructHighlightMaterial);

		return;

	}

	// Reset if changed

	if (highlightedBuildInstance == nullptr) return;

	highlightedBuildInstance->ResetHighlightMaterial();
	highlightedBuildInstance = nullptr;

}

void UConstructionModeManager::Confirm() {

	switch (tool) {

	case EConstructionTool::BuildTool: ConfirmBuildTool(); break;
	case EConstructionTool::DeconstructTool: ConfirmDeconstructTool(); break;
	default: break;

	}

}
void UConstructionModeManager::ConfirmBuildTool() {

	if (!m_buildGhost->IsValidPlacement()) {

		PW_LOG_ERROR(LogBuilding, TEXT("Invalid build placement."));
		return;

	}

	PW_LOG(LogBuilding, TEXT("Build action confirmed."));

	PW_ASSERT(buildInstanceClass != nullptr, LogBuilding, TEXT("Can't confirm build when no build instance class is set in BuildModeManager on actor '%s'."), *GetNameSafe(m_character));

	ABuildInstance* buildInstance = GetWorld()->SpawnActor<ABuildInstance>(buildInstanceClass, m_buildGhost->GetTransform());
	PW_ASSERT(buildInstance != nullptr, LogBuilding, TEXT("Could not spawn actor of type ABuildInstance."));

	buildInstance->SetBuild(testBuild);

}
void UConstructionModeManager::ConfirmDeconstructTool() {

	if (highlightedBuildInstance == nullptr) return;

	GetWorld()->DestroyActor(highlightedBuildInstance);
	highlightedBuildInstance = nullptr;

}

void UConstructionModeManager::ToggleGridSnap() {

	if (tool != EConstructionTool::BuildTool) return;
	gridSnap = !gridSnap;

}