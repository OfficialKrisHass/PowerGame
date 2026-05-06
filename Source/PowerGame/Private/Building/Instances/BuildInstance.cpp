#include "Building/Instances/BuildInstance.h"
#include "Building/Instances/Wire.h"

#include "Building/Build.h"

#include "Power/PowerNetwork.h"

ABuildInstance::ABuildInstance() {

	PrimaryActorTick.bCanEverTick = false;

}

void ABuildInstance::BeginPlay() {

	Super::BeginPlay();

}

void ABuildInstance::SetBuild(UBuild* build) {

	m_build = build;
	mesh->SetStaticMesh(build->mesh);

}

void ABuildInstance::ConnectWire(AWire* wire) {

	m_connectedWires.Add(wire);

}

void ABuildInstance::Deconstruct() {

	for (TObjectPtr<AWire> wire : m_connectedWires) {

		if (wire == nullptr || wire->IsActorBeingDestroyed()) continue;
		if (m_powerNetwork != nullptr)
			m_powerNetwork->DisconnectWire(wire);

		GetWorld()->DestroyActor(wire);

	}

}

void ABuildInstance::SetHighlightMaterial(UMaterialInterface* material) {

	mesh->SetOverlayMaterial(material);

}
void ABuildInstance::ResetHighlightMaterial() {

	mesh->SetOverlayMaterial(nullptr);

}