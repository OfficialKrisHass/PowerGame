#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "Core/Core.h"

#include "BuildInstance.generated.h"

class UBuild;

class AWire;
class APowerNetwork;

UCLASS(Abstract)
class POWERGAME_API ABuildInstance : public AActor {

	GENERATED_BODY()

	friend APowerNetwork;
	friend AWire;
	
public:
	ABuildInstance();

	UFUNCTION(BlueprintCallable)
	void SetBuild(UBuild* build);

	UFUNCTION(BlueprintCallable)
	virtual void ConnectWire(AWire* wire);

	UFUNCTION(BlueprintCallable)
	virtual void Deconstruct();

	// Highlight material

	UFUNCTION(BlueprintCallable)
	void SetHighlightMaterial(UMaterialInterface* material);
	UFUNCTION(BlueprintCallable)
	void ResetHighlightMaterial();

	// Getters

	UFUNCTION(BlueprintCallable)
	inline UBuild* GetBuild() const { return m_build; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuild> m_build = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APowerNetwork> m_powerNetwork = nullptr;
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<AWire>> m_connectedWires;

	
};
