#include "Building/Instances/MeshBuildInstance.h"

#include "Saving/BuildingSaveData.h"

AMeshBuildInstance::AMeshBuildInstance() {

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mesh);

}

void AMeshBuildInstance::SerializeSaveData(FInstancedStruct* out) {

	if (!out->IsValid() || !out->GetScriptStruct()->IsChildOf(FBuildingSaveData::StaticStruct()))
		out->InitializeAs<FBuildingSaveData>();

	Super::SerializeSaveData(out);

}

void AMeshBuildInstance::DeserializeSaveData(const FInstancedStruct& data) {

	Super::DeserializeSaveData(data);

}