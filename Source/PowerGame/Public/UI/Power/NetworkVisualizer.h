#pragma once

#include <CoreMinimal.h>
#include "UI/UserWidgetBase.h"
#include "NetworkVisualizer.generated.h"

class APowerNetwork;

UCLASS()
class POWERGAME_API UNetworkVisualizer : public UUserWidgetBase {

	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	inline void SetNetwork(APowerNetwork* network) { m_network = network; }

protected:
	virtual int32 NativePaint(const FPaintArgs& args, const FGeometry& allotedGeometry, const FSlateRect& cullingRect, FSlateWindowElementList& out, int32 layer, const FWidgetStyle& widgetStyle, bool parentEnabled) const override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APowerNetwork> m_network = nullptr;

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

	UPROPERTY()
	float phase = 0.0f;

};