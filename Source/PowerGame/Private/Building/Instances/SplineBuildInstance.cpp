#include "Building/Instances/SplineBuildInstance.h"

#include "Saving/WorldSaveSubsystem.h"
 
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>

#include <InstancedStruct.h>

ASplineBuildInstance::ASplineBuildInstance() {

	m_spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	m_spline->SetMobility(EComponentMobility::Movable);
	SetRootComponent(m_spline);

	m_splineMesh = CreateDefaultSubobject<USplineMeshComponent>(TEXT("Spline mesh"));
	m_splineMesh->SetMobility(EComponentMobility::Movable);
	m_splineMesh->SetupAttachment(m_spline);

	mesh = m_splineMesh;

}

void ASplineBuildInstance::SetStartAndEnd(const FVector& startLocation, const FVector& endLocation) {

	m_spline->SetLocationAtSplinePoint(0, startLocation, ESplineCoordinateSpace::World);
	m_spline->SetLocationAtSplinePoint(1, endLocation, ESplineCoordinateSpace::World);

	FVector dir = (endLocation - startLocation);
	float length = dir.Length();

	FVector startTangent = dir.GetSafeNormal() * length * 0.5f + FVector::DownVector * length * m_sagAmount;
	FVector endTangent = dir.GetSafeNormal() * length * 0.5f - FVector::DownVector * length * m_sagAmount;

	m_splineMesh->SetStartAndEnd(FVector::ZeroVector, startTangent, endLocation - startLocation, endTangent);

}

void ASplineBuildInstance::SerializeSaveData(FInstancedStruct* out) {

	PW_ASSERT(out->GetScriptStruct()->IsChildOf(FSplineSaveData::StaticStruct()), LogSaveSubsystem, TEXT("FInstancedStruct must be initialized by the most derived class."));
	
	Super::SerializeSaveData(out);

	FSplineSaveData& saveData = out->GetMutable<FSplineSaveData>();

	saveData.start = m_spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	saveData.end = m_spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);

	saveData.sagAmount = m_sagAmount;

}

void ASplineBuildInstance::DeserializeSaveData(const FInstancedStruct& data) {

	PW_ASSERT(data.GetScriptStruct()->IsChildOf(FSplineSaveData::StaticStruct()), LogSaveSubsystem, TEXT("Saved FInstancedStruct is not of type FSplineSaveData."));
	Super::DeserializeSaveData(data);

	const FSplineSaveData& saveData = data.Get<FSplineSaveData>();

	m_sagAmount = saveData.sagAmount;
	SetStartAndEnd(saveData.start, saveData.end);

}
