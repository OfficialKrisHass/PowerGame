#include "Building/Instances/Wire.h"

void AWire::SetStartAndEnd(const FVector& startLocation, const FVector& endLocation) {

	Super::SetStartAndEnd(startLocation, endLocation);

	m_startLocation = startLocation;
	m_endLocation = endLocation;

}