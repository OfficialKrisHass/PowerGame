#include "UI/Power/NetworkVisualizer.h"
#include "UI/Power/NetworkSineWaveVisualizer.h"

#include "UI/MainHUD.h"

#include "Power/PowerNetwork.h"

#include "Player/MainPlayerController.h"

#include <Components/TextBlock.h>

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

#define LOCTEXT_NAMESPACE "PowerGame"

void UNetworkVisualizer::InitializeUI(AMainPlayerController* controller) {

	PW_ASSERT(controller != nullptr, LogPower, TEXT("Can't initialize NetworkVisualizer UI with invalid controller."));

	m_controller = controller;
	SetOwningPlayer(controller);

	SetVisibility(ESlateVisibility::Hidden);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(m_controller->InputComponent);
	PW_ASSERT(inputComponent != nullptr, LogPower, TEXT("Could not retrieve UEnhancedInputComponent from '%s'."), *GetNameSafe(m_controller));

	inputComponent->BindAction(closeAction, ETriggerEvent::Triggered, this, &UNetworkVisualizer::Close);

}

void UNetworkVisualizer::NativeTick(const FGeometry& geometry, float deltaTime) {

	Super::NativeTick(geometry, deltaTime);

	if (m_network == nullptr) return;

	frequencyText->SetText(FText::FromString(FString::Printf(TEXT("Frequency: %.2f"), m_network->GetFrequency())));
	voltageText->SetText(FText::FromString(FString::Printf(TEXT("Voltage: %.2f"), m_network->GetVoltage())));

}

void UNetworkVisualizer::Open(APowerNetwork* network) {

	if (GetVisibility() == ESlateVisibility::Visible) return;

	if (!IsInViewport())
		AddToViewport();

	SetVisibility(ESlateVisibility::Visible);
	m_network = network;

	PW_ASSERT(m_controller != nullptr, LogUI, TEXT("NetworkVisualizer was not assigned a player controller, make sure you called UNetworkInitializer::InitializeUI()."));

	m_controller->SetShowMouseCursor(true);
	m_controller->SetInputMode(FInputModeGameAndUI());
	m_controller->DisableDefaultIMC();
	m_controller->AddMappingContext(uiIMC);

	sineWaveVisualizer->SetNetwork(m_network);

}
void UNetworkVisualizer::Close() {

	if (GetVisibility() == ESlateVisibility::Hidden) return;

	SetVisibility(ESlateVisibility::Hidden);
	m_network = nullptr;

	PW_ASSERT(m_controller != nullptr, LogUI, TEXT("NetworkVisualizer was not assigned a player controller, make sure you called UNetworkInitializer::InitializeUI()."));

	m_controller->SetShowMouseCursor(false);
	m_controller->SetInputMode(FInputModeGameOnly());
	m_controller->EnableDefaultIMC();
	m_controller->RemoveMappingContext(uiIMC);

	sineWaveVisualizer->SetNetwork(nullptr);

}