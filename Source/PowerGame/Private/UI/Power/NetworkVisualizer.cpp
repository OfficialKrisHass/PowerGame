#include "UI/Power/NetworkVisualizer.h"

#include "UI/MainHud.h"

#include "Power/PowerNetwork.h"

#include "Player/MainPlayerController.h"

#include <Rendering/DrawElements.h>

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

void UNetworkVisualizer::InitializeUI(AMainPlayerController* controller) {

	PW_ASSERT(controller != nullptr, LogPower, TEXT("Can't initialize NetworkVisualizer UI with invalid controller."));

	m_controller = controller;
	SetOwningPlayer(controller);

	SetVisibility(ESlateVisibility::Hidden);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(m_controller->InputComponent);
	PW_ASSERT(inputComponent != nullptr, LogPower, TEXT("Could not retrieve UEnhancedInputComponent from '%s'."), *GetNameSafe(m_controller));

	inputComponent->BindAction(closeAction, ETriggerEvent::Triggered, this, &UNetworkVisualizer::Close);

}

int32 UNetworkVisualizer::NativePaint(const FPaintArgs& args, const FGeometry& allotedGeometry, const FSlateRect& cullingRect, FSlateWindowElementList& out, int32 layer, const FWidgetStyle& widgetStyle, bool parentEnabled) const {

	Super::NativePaint(args, allotedGeometry, cullingRect, out, layer, widgetStyle, parentEnabled);

	if (m_network == nullptr || m_network->IsDead()) return layer;

	const FVector2D size = allotedGeometry.GetLocalSize();

	TArray<FVector2D> points;
	points.Reserve(numSamples);

	for (uint32 i = 0; i < numSamples; i++) {

		float t = (float) i / numSamples;
		float frequency = baseWaveCycles + ((m_network->GetFrequency() - m_network->GetBaseFrequency()) * amplification);

		float y = size.Y * 0.5f + FMath::Sin((t * frequency * PI * 2.0f) + phase) * amplitude;

		points.Add(FVector2D(t * size.X, y));

	}

	FSlateDrawElement::MakeLines(out, layer + 1, allotedGeometry.ToPaintGeometry(), points, ESlateDrawEffect::None, FLinearColor::Green, true, lineThickness);

	return layer + 1;

}
void UNetworkVisualizer::NativeTick(const FGeometry& geometry, float deltaTime) {

	Super::NativeTick(geometry, deltaTime);

	if (m_network == nullptr || m_network->IsDead()) return;

	phase += deltaTime * scrollSpeed;
	phase = FMath::Fmod(phase, PI * 2.0f);

}

void UNetworkVisualizer::Open(APowerNetwork* network) {

	if (!IsInViewport())
		AddToViewport();

	SetVisibility(ESlateVisibility::Visible);
	m_network = network;

	PW_ASSERT(m_controller != nullptr, LogUI, TEXT("NetworkVisualizer was not assigned a player controller, make sure you called UNetworkInitializer::InitializeUI()."));

	m_controller->SetShowMouseCursor(true);
	m_controller->SetInputMode(FInputModeGameAndUI());
	m_controller->DisableDefaultIMC();
	m_controller->AddMappingContext(m_visualizerIMC);

}
void UNetworkVisualizer::Close() {

	SetVisibility(ESlateVisibility::Hidden);
	m_network = nullptr;

	PW_ASSERT(m_controller != nullptr, LogUI, TEXT("NetworkVisualizer was not assigned a player controller, make sure you called UNetworkInitializer::InitializeUI()."));

	m_controller->SetShowMouseCursor(false);
	m_controller->SetInputMode(FInputModeGameOnly());
	m_controller->EnableDefaultIMC();
	m_controller->RemoveMappingContext(m_visualizerIMC);

}