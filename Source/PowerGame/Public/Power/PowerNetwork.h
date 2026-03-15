#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include <Logging/LogMacros.h>

#include "Core/Core.h"

#include "PowerNetwork.generated.h"

class ABuildInstance;

class AGenerator;
class ALoad;
class AWire;

DECLARE_LOG_CATEGORY_EXTERN(LogPower, Log, All);

UCLASS()
class POWERGAME_API APowerNetwork : public AActor {

	GENERATED_BODY()
	
public:
	APowerNetwork();

	UFUNCTION(BlueprintCallable)
	void ConnectGenerator(AGenerator* generator);
	UFUNCTION(BlueprintCallable)
	void ConnectLoad(ALoad* load);

	UFUNCTION(BlueprintCallable)
	static APowerNetwork* HandleConnection(ABuildInstance* buildInstanceA, ABuildInstance* buildInstanceB, AWire* wire);

private:
	UPROPERTY(VisibleAnywhere)
	float m_voltage = 0.0f;
	UPROPERTY(VisibleAnywhere)
	float m_frequency = 0.0f;
	UPROPERTY(VisibleAnywhere)
	float m_phaseAngle = 0.0f;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AWire>> m_connections;
	UPROPERTY(VisibleAnywhere)
	TSet<TObjectPtr<AGenerator>> m_generators;
	UPROPERTY(VisibleAnywhere)
	TSet<TObjectPtr<ALoad>> m_loads;

	void AddBuildInstance(ABuildInstance* buildInstance);
	
};