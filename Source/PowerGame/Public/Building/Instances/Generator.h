#pragma once

#include <CoreMinimal.h>
#include <Building/BuildInstance.h>

#include "Core/Core.h"

#include "Generator.generated.h"

UCLASS()
class POWERGAME_API AGenerator : public ABuildInstance {

	GENERATED_BODY()
	
public:
	//

protected:
	UPROPERTY(EditAnywhere)
	bool active = false;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float voltage = 230.0f;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float frequency = 50.0f;

};