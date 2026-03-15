#pragma once

#include <CoreMinimal.h>
#include "Building/Instances/SplineBuildInstance.h"

#include "Wire.generated.h"

class APowerNetwork;

UCLASS()
class POWERGAME_API AWire : public ASplineBuildInstance {

	GENERATED_BODY()

	friend APowerNetwork;
	
public:
	virtual void SetStartAndEnd(const FVector& startLocation, const FVector& endLocation) override;

	UFUNCTION(BlueprintCallable)
	void Connect(ABuildInstance* startBuildInstance, ABuildInstance* endBuildInstance);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuildInstance> m_startBuildInstance = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuildInstance> m_endBuildInstance = nullptr;

};