#pragma once

#include <CoreMinimal.h>
#include <InstancedStruct.h>

#include "Core/Core.h"

#include "BuildingSaveData.generated.h"

class UBuild;

class ABuildInstance;

USTRUCT()
struct FBuildingSaveData {

	GENERATED_BODY()

	UPROPERTY()
	FGuid guid;
	UPROPERTY()
	TObjectPtr<UBuild> build = nullptr;
	UPROPERTY()
	TSubclassOf<ABuildInstance> buildClass = nullptr;

	UPROPERTY()
	FTransform transform;

};
