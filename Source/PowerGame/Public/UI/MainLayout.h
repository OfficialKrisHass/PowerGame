#pragma once

#include <CoreMinimal.h>
#include <UI/UserWidgetBase.h>

#include "Core/Core.h"

#include "MainLayout.generated.h"

class UBuildMenu;

UCLASS(Abstract)
class POWERGAME_API UMainLayout : public UUserWidgetBase {

	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UBuildMenu> buildMenu = nullptr;

};