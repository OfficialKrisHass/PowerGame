#pragma once

#include <CoreMinimal.h>
#include "UI/UserWidgetBase.h"

#include "Core/Core.h"

#include "BuildMenu.generated.h"

class AMainPlayerController;

class UBuild;
class UBuildSlot;

class UWrapBox;

UCLASS(Abstract)
class POWERGAME_API UBuildMenu : public UUserWidgetBase {

	GENERATED_BODY()
	
public:
	void InitializeUI(AMainPlayerController* controller);

	UFUNCTION(BlueprintCallable)
	void Open();
	UFUNCTION(BlueprintCallable)
	void Close();

	UFUNCTION(BlueprintCallable)
	void UpdateSlots(const TArray<UBuild*>& builds);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UWrapBox> slotsParent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuildSlot> buildSlotClass = nullptr;

private:
	UPROPERTY()
	TObjectPtr<AMainPlayerController> m_controller;

	UPROPERTY()
	TArray<TObjectPtr<UBuildSlot>> slots;

};