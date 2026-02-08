#include "UI/MainHUD.h"
#include "UI/MainLayout.h"

#include "Player/MainPlayerController.h"

DEFINE_LOG_CATEGORY(LogUI);

void AMainHUD::BeginPlay() {

	Super::BeginPlay();

	AMainPlayerController* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	PW_ASSERT(controller != nullptr, LogUI, TEXT("Could not retrieve AMainPlayerController."));

	PW_ASSERT(layoutClass != nullptr, LogUI, TEXT("layoutClass was not assigned on AMainHUD."));
	m_layout = CreateWidget<UMainLayout>(controller, layoutClass);
	m_layout->AddToViewport();
	m_layout->SetVisibility(ESlateVisibility::Visible);

}