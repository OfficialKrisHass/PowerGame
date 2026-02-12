#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "Core/Core.h"

#include "PowerNetwork.generated.h"

UCLASS()
class POWERGAME_API APowerNetwork : public AActor {

	GENERATED_BODY()
	
public:
	APowerNetwork();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	float voltage = 0.0f;
	UPROPERTY(VisibleAnywhere)
	float frequency = 0.0f;
	UPROPERTY(VisibleAnywhere)
	float phaseAngle = 0.0f;
	
};