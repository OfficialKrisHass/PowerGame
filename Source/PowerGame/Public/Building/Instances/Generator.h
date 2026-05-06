#pragma once

#include <CoreMinimal.h>
#include <Building/Instances/MeshBuildInstance.h>

#include "Core/Core.h"

#include "Generator.generated.h"

UCLASS()
class POWERGAME_API AGenerator : public AMeshBuildInstance {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Respond(float freqError);

	UFUNCTION(BlueprintCallable)
	inline float GetMaxOutput() const { return maxOutput; }
	UFUNCTION(BlueprintCallable)
	inline float GetCurrentOutput() const { return m_currentOutput; }

	UFUNCTION(BlueprintCallable)
	inline void SetNetwork(APowerNetwork* network) { m_network = network; }
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type reason) override;

private:
	UPROPERTY(EditAnywhere, Category = "Properties")
	float maxOutput = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float responseStrength = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float m_currentOutput = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Power network")
	TObjectPtr<APowerNetwork> m_network  = nullptr;

};