#pragma once

#include <CoreMinimal.h>
#include "UI/UserWidgetBase.h"

#include "Core/Core.h"

#include "NetworkSineWaveVisualizer.generated.h"

class APowerNetwork;

UCLASS(Abstract)
class POWERGAME_API UNetworkSineWaveVisualizer : public UUserWidgetBase {

	GENERATED_BODY()
	
public:
	inline void SetNetwork(APowerNetwork* network) { m_network = network; }

protected:
	virtual int32 NativePaint(const FPaintArgs& args, const FGeometry& allotedGeometry, const FSlateRect& cullingRect, FSlateWindowElementList& out, int32 layer, const FWidgetStyle& widgetStyle, bool parentEnabled) const override;
	virtual void NativeTick(const FGeometry& geometry, float deltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APowerNetwork> m_network = nullptr;
	UPROPERTY(EditAnywhere)
	bool showDebugWave = false;
	UPROPERTY(EditAnywhere)
	float debugFrequency = 50.0f;

	// Wave visualization

	UPROPERTY(EditAnywhere, Category = "Wave")
	uint32 numSamples = 128;

	UPROPERTY(EditAnywhere, Category = "Wave")
	uint32 baseWaveCycles = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Wave")
	float lineThickness = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Wave")
	float amplitude = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Wave")
	float scrollSpeed = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Wave")
	float frequencyDiffMin = -10.0f;
	UPROPERTY(EditAnywhere, Category = "Wave")
	float frequencyDiffMax = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Wave")
	float amplification = 5.0f;

	// Quality visualization

	UPROPERTY(EditAnywhere, Category = "Quality visualization")
	FLinearColor normalQualityColor;
	UPROPERTY(EditAnywhere, Category = "Quality visualization")
	FLinearColor lowQualityColor;
	UPROPERTY(EditAnywhere, Category = "Quality visualization")
	FLinearColor highQualityColor;

	// Grid lines

	UPROPERTY(EditAnywhere, Category = "Grid")
	uint32 majorGridSegments = 3;
	UPROPERTY(EditAnywhere, Category = "Grid")
	uint32 minorGridSegments = 2;

	UPROPERTY(EditAnywhere, Category = "Grid")
	float gridLineThickness = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FLinearColor majorLineColor;
	UPROPERTY(EditAnywhere, Category = "Grid")
	FLinearColor minorLineColor;
	UPROPERTY(EditAnywhere, Category = "Grid")
	FLinearColor centerLineColor;

	// Misc

	UPROPERTY()
	float m_phase = 0.0f;

	void DrawGrid(const FGeometry& allotedGeometry, FSlateWindowElementList& out, int32& layer) const;

};