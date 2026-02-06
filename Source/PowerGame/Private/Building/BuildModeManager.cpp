#include "Building/BuildModeManager.h"
#include "Building/BuildGhost.h"
#include "Building/BuildInstance.h"

#include "Player/MainPlayerCharacter.h"
#include "Player/MainPlayerController.h"

#include <Camera/CameraComponent.h>

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputAction.h>

DEFINE_LOG_CATEGORY(LogBuilding);

UBuildModeManager::UBuildModeManager() {
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UBuildModeManager::BeginPlay() {

	Super::BeginPlay();

	m_character = Cast<AMainPlayerCharacter>(GetOwner());
	PW_ASSERT(m_character != nullptr, LogBuilding, TEXT("Build Mode Manager must be attached to actor of type AMainPlayerCharacter."));

	m_camera = m_character->GetCamera();
	PW_ASSERT(m_camera != nullptr, LogBuilding, TEXT("Could not retrieve UCameraComponent from '%s'."), *GetNameSafe(m_character));

	// Setup input

	m_controller = Cast<AMainPlayerController>(m_character->Controller);
	PW_ASSERT(m_controller != nullptr, LogBuilding, TEXT("Could not cast controller of '%s' to AMainPlayerController."), *GetNameSafe(m_character));
	PW_ASSERT(buildModeIMC != nullptr, LogBuilding, TEXT("No Build mode IMC assigned to the Build Mode Manager "));

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(m_character->InputComponent);
	PW_ASSERT(inputComponent != nullptr, LogBuilding, TEXT("Could not retrieve UEnhancedInputComponent from '%s'."), *GetNameSafe(m_character));

	inputComponent->BindAction(endBuildModeAction, ETriggerEvent::Started, this, &UBuildModeManager::EndBuildMode);
	inputComponent->BindAction(buildAction, ETriggerEvent::Started, this, &UBuildModeManager::Build);

	// Setup build ghost

	SpawnBuildGhost();

}
void UBuildModeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!buildModeActive) return;

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

	m_buildGhost->SetActorLocation(hit.ImpactPoint);

}

void UBuildModeManager::StartBuildMode() {

	if (buildModeActive) return;

	PW_LOG(LogBuilding, TEXT("Entering build mode"));

	m_controller->AddMappingContext(buildModeIMC);
	buildModeActive = true;

	m_buildGhost->SetActorHiddenInGame(false);
	m_buildGhost->SetBuild(testBuild);

}
void UBuildModeManager::EndBuildMode() {

	PW_LOG(LogBuilding, TEXT("Leaving build mode."));

	m_controller->RemoveMappingContext(buildModeIMC);
	buildModeActive = false;

	m_buildGhost->SetActorHiddenInGame(true);

}

void UBuildModeManager::Build() {

	PW_LOG(LogBuilding, TEXT("Build action confirmed."));

	PW_ASSERT(buildInstanceClass != nullptr, LogBuilding, TEXT("Can't confirm build when no build instance class is set in BuildModeManager on actor '%s'."), *GetNameSafe(m_character));

	ABuildInstance* buildInstance = GetWorld()->SpawnActor<ABuildInstance>(buildInstanceClass, m_buildGhost->GetTransform());
	PW_ASSERT(buildInstance != nullptr, LogBuilding, TEXT("Could not spawn actor of type ABuildInstance."));

	buildInstance->SetBuild(testBuild);

	EndBuildMode();

}

void UBuildModeManager::SpawnBuildGhost() {

	PW_ASSERT(buildGhostClass != nullptr, LogBuilding, TEXT("Can't spawn Build Ghost actor when no Build Ghost class is set in BuildModeManager."));

	FActorSpawnParameters params;
	params.Owner = GetOwner();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_buildGhost = GetWorld()->SpawnActor<ABuildGhost>(buildGhostClass, FTransform::Identity, params);
	PW_ASSERT(m_buildGhost != nullptr, LogBuilding, TEXT("Could not spawn Build Ghost actor."));

}