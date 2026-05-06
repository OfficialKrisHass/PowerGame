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
	void DisconnectGenerator(AGenerator* generator);
	UFUNCTION(BlueprintCallable)
	void DisconnectLoad(ALoad* load);
	UFUNCTION(BlueprintCallable)
	void DisconnectWire(AWire* wire);

	UFUNCTION(BlueprintCallable)
	static APowerNetwork* HandleConnection(ABuildInstance* buildInstanceA, ABuildInstance* buildInstanceB, AWire* wire);

protected:
	UPROPERTY(EditAnywhere)
	float baseFrequency = 50.0f;
	UPROPERTY(EditAnywhere)
	float baseVoltage = 230.0f;

private:
	UPROPERTY(VisibleAnywhere)
	bool m_dead = true;
	UPROPERTY(VisibleAnywhere)
	float m_voltage = 0.0f;
	UPROPERTY(VisibleAnywhere)
	float m_frequency = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float m_totalSupply = 0.0f;
	UPROPERTY(VisibleAnywhere)
	float m_totalDemand = 0.0f;

	UPROPERTY(VisibleAnywhere)
	TSet<TObjectPtr<AWire>> m_connections;
	UPROPERTY(VisibleAnywhere)
	TSet<TObjectPtr<AGenerator>> m_generators;
	UPROPERTY(VisibleAnywhere)
	TSet<TObjectPtr<ALoad>> m_loads;

	virtual void Tick(float deltaTime) override;

	void AddBuildInstance(ABuildInstance* buildInstance);
	
};