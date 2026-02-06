#include "Building/BuildGhost.h"
#include "Building/Build.h"

ABuildGhost::ABuildGhost() {

	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(mesh);

}

void ABuildGhost::BeginPlay() {

	Super::BeginPlay();

}

void ABuildGhost::SetBuild(UBuild* build) {

	m_build = build;
	mesh->SetStaticMesh(build->mesh);

}