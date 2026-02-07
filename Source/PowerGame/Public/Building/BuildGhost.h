#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "BuildGhost.generated.h"

class UBuild;

class UBoxComponent;

UCLASS()
class POWERGAME_API ABuildGhost : public AActor {

	GENERATED_BODY()
	
public:
	ABuildGhost();

	UFUNCTION(BlueprintCallable)
	void SetBuild(UBuild* build);

	UFUNCTION(BlueprintCallable)
	inline bool IsValidPlacement() const { return m_validPlacement; }

protected:
	UPROPERTY(EditAnywhere, Category = "Preview")
	TObjectPtr<UMaterialInterface> validMaterial = nullptr;
	UPROPERTY(EditAnywhere, Category = "Preview")
	TObjectPtr<UMaterialInterface> invalidMaterial = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> trigger = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuild> m_build = nullptr;

	UPROPERTY(VisibleAnywhere)
	bool m_validPlacement = true;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex, bool fromSweep, const FHitResult& sweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherIndex);
	
};