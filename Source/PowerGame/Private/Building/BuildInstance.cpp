#include "Building/BuildInstance.h"
#include "Building/Build.h"

ABuildInstance::ABuildInstance() {

	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(mesh);

}

void ABuildInstance::BeginPlay() {

	Super::BeginPlay();

}

void ABuildInstance::SetBuild(UBuild* build) {

	m_build = build;
	mesh->SetStaticMesh(build->mesh);

}

void ABuildInstance::SetHighlightMaterial(UMaterialInterface* material) {

	mesh->SetOverlayMaterial(material);

}
void ABuildInstance::ResetHighlightMaterial() {

	mesh->SetOverlayMaterial(nullptr);

}