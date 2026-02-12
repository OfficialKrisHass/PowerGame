#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "BuildGhost.generated.h"

class UBuild;

UENUM(BlueprintType)
enum class EBuildGhostState : uint8 {

	None = 0 UMETA(DisplayName = "None"),
	Preview = 1 UMETA(DisplayName = "Preview"),
	StartSelected = 2 UMETA(DisplayName = "Start locker"),

};

UCLASS(Abstract)
class POWERGAME_API ABuildGhost : public AActor {

	GENERATED_BODY()
	
public:
	ABuildGhost();

	UFUNCTION(BlueprintCallable)
	virtual void SetBuild(UBuild* build);

	UFUNCTION(BlueprintCallable)
	virtual void Update(const FVector& hitLocation, ABuildInstance* hitBuildInstance);

	UFUNCTION(BlueprintCallable)
	virtual void Confirm(const FVector& location);

	UFUNCTION(BlueprintCallable)
	virtual void Reset();

	// Getters

	UFUNCTION(BlueprintCallable)
	inline UBuild* GetBuild() const { return m_build; }

	UFUNCTION(BlueprintCallable)
	virtual inline bool IsValidPlacement() const { return true; }

protected:
	UPROPERTY(VisibleAnywhere)
	EBuildGhostState m_state = EBuildGhostState::None;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuild> m_build = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> m_mesh = nullptr;

private:
	virtual void BeginPlay() override;
	
};