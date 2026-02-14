#pragma once

#include <CoreMinimal.h>
#include "Building/Instances/BuildInstance.h"

#include "SplineBuildInstance.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class POWERGAME_API ASplineBuildInstance : public ABuildInstance {

	GENERATED_BODY()

public:
	ASplineBuildInstance();

	UFUNCTION(BlueprintCallable)
	virtual void SetStartAndEnd(const FVector& startLocation, const FVector& endLocation);

private:
	UPROPERTY(EditAnywhere)
	float m_sagAmount = 0.17f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> m_spline = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineMeshComponent> m_splineMesh = nullptr;

};