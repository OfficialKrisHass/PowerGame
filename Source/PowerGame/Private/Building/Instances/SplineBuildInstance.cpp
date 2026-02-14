#include "Building/Instances/SplineBuildInstance.h"

#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>

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