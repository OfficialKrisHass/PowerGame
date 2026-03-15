#pragma once

#include <CoreMinimal.h>
#include <Building/Instances/MeshBuildInstance.h>

#include "Core/Core.h"

#include "Generator.generated.h"

UCLASS()
class POWERGAME_API AGenerator : public AMeshBuildInstance {

	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	bool active = false;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float voltage = 230.0f;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float frequency = 50.0f;

};