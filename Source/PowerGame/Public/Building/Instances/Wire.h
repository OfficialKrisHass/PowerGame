#pragma once

#include <CoreMinimal.h>
#include "Building/BuildInstance.h"

#include "Wire.generated.h"

UCLASS()
class POWERGAME_API AWire : public ABuildInstance {

	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetStartAndEnd(const FVector& startLocation, const FVector& endLocation);

private:
	UPROPERTY(VisibleAnywhere)
	FVector m_startLocation = FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere)
	FVector m_endLocation = FVector::ZeroVector;

};