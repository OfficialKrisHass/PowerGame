#pragma once

#include <CoreMinimal.h>
#include "UI/UserWidgetBase.h"

#include "Core/Core.h"

#include "NetworkVisualizer.generated.h"

class UNetworkSineWaveVisualizer;

class AMainPlayerController;

class APowerNetwork;

// UE classes

class UTextBlock;

class UInputAction;
class UInputMappingContext;

UCLASS(Abstract)
class POWERGAME_API UNetworkVisualizer : public UUserWidgetBase {

	GENERATED_BODY()
	
public:
	void InitializeUI(AMainPlayerController* controller);

	UFUNCTION(BlueprintCallable)
	void Open(APowerNetwork* network);
	UFUNCTION(BlueprintCallable)
	void Close();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UNetworkSineWaveVisualizer> sineWaveVisualizer = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UTextBlock> frequencyText = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	TObjectPtr<UTextBlock> voltageText = nullptr;

	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APowerNetwork> m_network = nullptr;

	// Input

	// TODO: This should be moved to a general UI IMC.
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> closeAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> m_visualizerIMC = nullptr;

	UPROPERTY()
	TObjectPtr<AMainPlayerController> m_controller;

};