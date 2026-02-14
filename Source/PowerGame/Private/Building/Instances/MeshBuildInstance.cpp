#include "Building/Instances/MeshBuildInstance.h"

AMeshBuildInstance::AMeshBuildInstance() {

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mesh);

}