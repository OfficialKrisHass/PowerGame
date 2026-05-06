#pragma once

#include <CoreMinimal.h>
#include <Building/Instances/MeshBuildInstance.h>

#include "Core/Core.h"

#include "Load.generated.h"

UCLASS()
class POWERGAME_API ALoad : public AMeshBuildInstance {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Update(float supplyRatio);

	UFUNCTION(BlueprintCallable)
	inline float GetDemand() const { return demand; }

	UFUNCTION(BlueprintCallable)
	inline void SetNetwork(APowerNetwork* network) { m_network = network; }

protected:
	virtual void EndPlay(const EEndPlayReason::Type reason) override;

private:
	UPROPERTY(EditAnywhere, Category = "Properties")
	float demand = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float m_suppliedPower = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Power network")
	TObjectPtr<APowerNetwork> m_network = nullptr;

};