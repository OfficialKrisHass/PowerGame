#pragma once

#include <CoreMinimal.h>
#include <UI/UserWidgetBase.h>

#include "Core/Core.h"

#include "MainLayout.generated.h"

class UBuildMenu;
class UNetworkVisualizer;

UCLASS(Abstract)
class POWERGAME_API UMainLayout : public UUserWidgetBase {

	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	inline UNetworkVisualizer* GetNetworkVisualizer() const { return networkVisualizer; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UBuildMenu> buildMenu = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UNetworkVisualizer> networkVisualizer = nullptr;

};