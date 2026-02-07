#include "Player/MainPlayerCharacter.h"

#include "Building/ConstructionModeManager.h"

#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Camera/CameraComponent.h>

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputActionValue.h>

DEFINE_LOG_CATEGORY(LogCharacter)

AMainPlayerCharacter::AMainPlayerCharacter() {

	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	// Camera setup

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(GetCapsuleComponent());
	camera->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));
	camera->bUsePawnControlRotation = true;

	// Arm mesh setup

	armMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	armMesh->SetupAttachment(camera);
	armMesh->SetOnlyOwnerSee(true);
	armMesh->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.0f));
	armMesh->bCastDynamicShadow = false;
	armMesh->CastShadow = false;

	// Build mode setup

	constructionModeManager = CreateDefaultSubobject<UConstructionModeManager>(TEXT("BuildModeManager"));

}

void AMainPlayerCharacter::BeginPlay() {

	Super::BeginPlay();

}

void AMainPlayerCharacter::Move(const FInputActionValue& value) {

	FVector2D movementVector = value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), movementVector.Y);
	AddMovementInput(GetActorRightVector(), movementVector.X);

}
void AMainPlayerCharacter::Look(const FInputActionValue& value) {

	FVector2D lookVector = value.Get<FVector2D>();

	AddControllerYawInput(lookVector.X);
	AddControllerPitchInput(lookVector.Y);

}


void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent) {

	Super::SetupPlayerInputComponent(playerInputComponent);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(playerInputComponent);
	PW_ASSERT(inputComponent != nullptr, LogCharacter, TEXT("'%s' could not get the Enhanced input component."), *GetNameSafe(this));

	// Movement

	inputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Move);
	inputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Look);

	inputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	inputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	// Mode switching

	inputComponent->BindAction(selectBuildToolAction, ETriggerEvent::Started, constructionModeManager.Get(), &UConstructionModeManager::SelectBuildTool);
	inputComponent->BindAction(selectDeconstructToolAction, ETriggerEvent::Started, constructionModeManager.Get(), &UConstructionModeManager::SelectDeconstructTool);

}
