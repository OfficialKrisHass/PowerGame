#pragma once

#include <CoreMinimal.h>
#include "UI/UserWidgetBase.h"
#include "NetworkVisualizer.generated.h"

class AMainPlayerController;

class APowerNetwork;

class UInputAction;
class UInputMappingContext;

UCLASS()
class POWERGAME_API UNetworkVisualizer : public UUserWidgetBase {

	GENERATED_BODY()
	
public:
	void InitializeUI(AMainPlayerController* controller);

	UFUNCTION(BlueprintCallable)
	void Open(APowerNetwork* network);
	UFUNCTION(BlueprintCallable)
	void Close();

protected:
	virtual int32 NativePaint(const FPaintArgs& args, const FGeometry& allotedGeometry, const FSlateRect& cullingRect, FSlateWindowElementList& out, int32 layer, const FWidgetStyle& widgetStyle, bool parentEnabled) const override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APowerNetwork> m_network = nullptr;

	// Visualization knobs

	UPROPERTY(EditAnywhere)
	uint32 numSamples = 128;

	UPROPERTY(EditAnywhere)
	uint32 baseWaveCycles = 2.0f;
	UPROPERTY(EditAnywhere)
	float lineThickness = 2.0f;
	UPROPERTY(EditAnywhere)
	float amplitude = 50.0f;
	UPROPERTY(EditAnywhere)
	float scrollSpeed = 2.0f;

	UPROPERTY(EditAnywhere)
	float amplification = 5.0f;

	// Input

	// TODO: This should be moved to a general UI IMC.
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> closeAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> m_visualizerIMC = nullptr;

	UPROPERTY()
	TObjectPtr<AMainPlayerController> m_controller;

	UPROPERTY()
	float phase = 0.0f;

};