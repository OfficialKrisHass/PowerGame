#include "Building/BuildGhost.h"
#include "Building/Build.h"

#include <Components/BoxComponent.h>

ABuildGhost::ABuildGhost() {

	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(mesh);

	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	trigger->SetupAttachment(mesh);

	trigger->OnComponentBeginOverlap.AddDynamic(this, &ABuildGhost::OnOverlapBegin);
	trigger->OnComponentEndOverlap.AddDynamic(this, &ABuildGhost::OnOverlapEnd);

}

void ABuildGhost::BeginPlay() {

	Super::BeginPlay();

}

void ABuildGhost::SetBuild(UBuild* build) {

	m_build = build;
	mesh->SetStaticMesh(build->mesh);

}

void ABuildGhost::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex, bool fromSweep, const FHitResult& sweepResult) {

	mesh->SetMaterial(0, invalidMaterial);
	m_validPlacement = false;

}

void ABuildGhost::OnOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex) {

	mesh->SetMaterial(0, validMaterial);
	m_validPlacement = true;

}