#include "Building/BuildGhostNormal.h"

#include <Components/BoxComponent.h>

ABuildGhostNormal::ABuildGhostNormal() {

	validityTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Validity trigger"));
	validityTrigger->SetupAttachment(m_mesh);

	validityTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABuildGhostNormal::OnOverlapBegin);
	validityTrigger->OnComponentEndOverlap.AddDynamic(this, &ABuildGhostNormal::OnOverlapEnd);

}

// Placement validation

void ABuildGhostNormal::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex, bool fromSweep, const FHitResult& sweepResult) {

	m_mesh->SetOverlayMaterial(m_invalidMaterial);
	m_validPlacement = false;

}

void ABuildGhostNormal::OnOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex) {

	m_mesh->SetOverlayMaterial(m_validMaterial);
	m_validPlacement = true;

}