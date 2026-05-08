#include "UI/Power/NetworkVisualizer.h"

#include "Power/PowerNetwork.h"

#include <Rendering/DrawElements.h>

int32 UNetworkVisualizer::NativePaint(const FPaintArgs& args, const FGeometry& allotedGeometry, const FSlateRect& cullingRect, FSlateWindowElementList& out, int32 layer, const FWidgetStyle& widgetStyle, bool parentEnabled) const {

	Super::NativePaint(args, allotedGeometry, cullingRect, out, layer, widgetStyle, parentEnabled);

	if (m_network == nullptr || m_network->IsDead()) return layer;

	const FVector2D size = allotedGeometry.GetLocalSize();

	TArray<FVector2D> points;
	points.Reserve(numSamples);

	for (uint32 i = 0; i < numSamples; i++) {

		float t = (float) i / numSamples;
		float frequency = baseWaveCycles + ((m_network->GetFrequency() - m_network->GetBaseFrequency()) * amplification);

		float y = size.Y * 0.5f + FMath::Sin((t * frequency * PI * 2.0f) + phase) * amplitude;

		points.Add(FVector2D(t * size.X, y));

	}

	FSlateDrawElement::MakeLines(out, layer + 1, allotedGeometry.ToPaintGeometry(), points, ESlateDrawEffect::None, FLinearColor::Green, true, lineThickness);

	return layer + 1;

}
void UNetworkVisualizer::NativeTick(const FGeometry& geometry, float deltaTime) {

	Super::NativeTick(geometry, deltaTime);

	if (m_network == nullptr || m_network->IsDead()) return;

	phase += deltaTime * scrollSpeed;
	phase = FMath::Fmod(phase, PI * 2.0f);

}