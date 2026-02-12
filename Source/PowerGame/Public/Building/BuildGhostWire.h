#pragma once

#include <CoreMinimal.h>
#include <Building/BuildGhost.h>

#include "BuildGhostWire.generated.h"

UCLASS()
class POWERGAME_API ABuildGhostWire : public ABuildGhost {

	GENERATED_BODY()

public:
	virtual void SetBuild(UBuild* build) override;

	virtual void Update(const FVector& hitLocation, ABuildInstance* hitBuildInstance) override;

	virtual void Confirm(const FVector& location) override;

private:
	UPROPERTY(VisibleAnywhere)
	FVector m_startLocation = FVector::ZeroVector;

};