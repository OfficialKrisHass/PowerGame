#pragma once

#include <CoreMinimal.h>
#include "Building/Instances/BuildInstance.h"
#include <StructUtils.h>

#include "Core/Core.h"

#include "MeshBuildInstance.generated.h"

UCLASS()
class POWERGAME_API AMeshBuildInstance : public ABuildInstance {

	GENERATED_BODY()

public:
	AMeshBuildInstance();

	virtual void SerializeSaveData(FInstancedStruct* out) override;
	virtual void DeserializeSaveData(const FInstancedStruct& data) override;

};