#pragma once

#include <CoreMinimal.h>
#include <GameFramework/HUD.h>

#include "Core/Core.h"

#include "MainHUD.generated.h"

class UMainLayout;

DECLARE_LOG_CATEGORY_EXTERN(LogUI, Log, All);

UCLASS(Abstract)
class POWERGAME_API AMainHUD : public AHUD {

	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainLayout> layoutClass = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UMainLayout> m_layout = nullptr;

	virtual void BeginPlay() override;

};