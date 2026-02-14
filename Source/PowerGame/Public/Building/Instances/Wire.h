#pragma once

#include <CoreMinimal.h>
#include "Building/Instances/SplineBuildInstance.h"

#include "Wire.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class POWERGAME_API AWire : public ASplineBuildInstance {

	GENERATED_BODY()
	
public:
	virtual void SetStartAndEnd(const FVector& startLocation, const FVector& endLocation) override;

private:
	UPROPERTY(VisibleAnywhere)
	FVector m_startLocation = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere)
	FVector m_endLocation = FVector::ZeroVector;

};