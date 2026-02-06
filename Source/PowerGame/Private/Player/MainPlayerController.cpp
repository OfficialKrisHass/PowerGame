#include "Player/MainPlayerController.h"
#include "Player/MainPlayerCharacter.h"

#include <Engine/LocalPlayer.h>

#include <EnhancedInputSubsystems.h>

void AMainPlayerController::BeginPlay() {

	Super::BeginPlay();

	m_inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	PW_ASSERT(m_inputSubsystem != nullptr, LogCharacter, TEXT("'%s' could not retrieve Enhanced input local player subsystem."), *GetNameSafe(this));

	EnableDefaultIMC();

}

void AMainPlayerController::EnableDefaultIMC() {

	AddMappingContext(defaultIMC, 0);

}
void AMainPlayerController::DisableDefaultIMC() {

	RemoveMappingContext(defaultIMC);

}

void AMainPlayerController::AddMappingContext(UInputMappingContext* imc, int priority) {

	m_inputSubsystem->AddMappingContext(imc, priority);

}
void AMainPlayerController::RemoveMappingContext(UInputMappingContext* imc) {

	m_inputSubsystem->RemoveMappingContext(imc);

}