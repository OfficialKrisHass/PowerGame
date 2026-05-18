#pragma once

#include <CoreMinimal.h>
#include "Building/Instances/SplineBuildInstance.h"

#include "Core/Core.h"

#include "Wire.generated.h"

class APowerNetwork;

USTRUCT()
struct FWireSaveData : public FSplineSaveData {

	GENERATED_BODY()

	UPROPERTY()
	FGuid startGUID;
	UPROPERTY()
	FGuid endGUID;

};

UCLASS()
class POWERGAME_API AWire : public ASplineBuildInstance {

	GENERATED_BODY()

	friend APowerNetwork;
	
public:
	virtual void SetStartAndEnd(const FVector& startLocation, const FVector& endLocation) override;

	UFUNCTION(BlueprintCallable)
	void Connect(ABuildInstance* startBuildInstance, ABuildInstance* endBuildInstance);

	virtual void SerializeSaveData(FInstancedStruct* out) override;
	virtual void DeserializeSaveData(const FInstancedStruct& data) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuildInstance> m_startBuildInstance = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuildInstance> m_endBuildInstance = nullptr;

};