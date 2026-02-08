#include "UI/MainLayout.h"
#include "UI/MainHUD.h"

#include "UI/BuildMenu/BuildMenu.h"

#include "Player/MainPlayerController.h"
#include "Player/MainPlayerCharacter.h"

#include "Building/ConstructionModeManager.h"

void UMainLayout::NativeConstruct() {

	Super::NativeConstruct();

	AMainPlayerController* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	PW_ASSERT(controller != nullptr, LogUI, TEXT("Could not retrieve first player controller."));

	AMainPlayerCharacter* character = Cast<AMainPlayerCharacter>(controller->GetCharacter());
	PW_ASSERT(character != nullptr, LogUI, TEXT("Could not retrieve player character from player controller."));

	PW_ASSERT(buildMenu != nullptr, LogUI, TEXT("Build Menu ui was not assigned."));

	character->GetConstructionModeManager()->BindUI(buildMenu);
	buildMenu->InitializeUI(controller);

}