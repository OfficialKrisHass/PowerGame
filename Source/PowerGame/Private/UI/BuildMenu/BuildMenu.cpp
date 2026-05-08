#include "UI/BuildMenu/BuildMenu.h"
#include "UI/BuildMenu/BuildSlot.h"

#include "UI/MainHUD.h"

#include "Player/MainPlayerController.h"

#include <Components/WrapBox.h>

void UBuildMenu::InitializeUI(AMainPlayerController* controller) {

	m_controller = controller;
	SetOwningPlayer(controller);

	SetVisibility(ESlateVisibility::Hidden);

}

void UBuildMenu::UpdateSlots(const TArray<UBuild*>& builds) {

	PW_ASSERT(buildSlotClass != nullptr, LogUI, TEXT("Build slot Class must be assigned."));

	for (UBuild* build : builds) {

		UBuildSlot* slot = CreateWidget<UBuildSlot>(GetOwningPlayer(), buildSlotClass);

		slot->SetBuild(build);
		slotsParent->AddChild(slot);

		slots.Add(slot);

	}

}

void UBuildMenu::Open() {

	if (!IsInViewport())
		AddToViewport();

	SetVisibility(ESlateVisibility::Visible);

	PW_ASSERT(m_controller != nullptr, LogUI, TEXT("Build menu was not assigned a player controller, make sure you called UBuildMenu::InitializeUI()."));

	m_controller->SetShowMouseCursor(true);
	m_controller->SetInputMode(FInputModeGameAndUI());
	m_controller->DisableDefaultIMC();

}
void UBuildMenu::Close() {

	SetVisibility(ESlateVisibility::Hidden);

	PW_ASSERT(m_controller != nullptr, LogUI, TEXT("Build menu was not assigned a player controller, make sure you called UBuildMenu::InitializeUI()."));
	
	m_controller->SetShowMouseCursor(false);
	m_controller->SetInputMode(FInputModeGameOnly());
	m_controller->EnableDefaultIMC();

}