#pragma once

#include <CoreMinimal.h>
#include "UI/UserWidgetBase.h"

#include "Core/Core.h"

#include "BuildSlot.generated.h"

class UBuild;

class UButton;
class UImage;

UCLASS(Abstract)
class POWERGAME_API UBuildSlot : public UUserWidgetBase {

	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetBuild(UBuild* build);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UButton> button = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UImage> icon = nullptr;

	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuild> m_build = nullptr;

	UFUNCTION()
	void Select();

};