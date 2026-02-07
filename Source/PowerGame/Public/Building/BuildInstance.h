#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "Core/Core.h"

#include "BuildInstance.generated.h"

class UBuild;

UCLASS()
class POWERGAME_API ABuildInstance : public AActor {

	GENERATED_BODY()
	
public:
	ABuildInstance();

	UFUNCTION(BlueprintCallable)
	void SetBuild(UBuild* build);

	UFUNCTION(BlueprintCallable)
	void SetHighlightMaterial(UMaterialInterface* material);
	UFUNCTION(BlueprintCallable)
	void ResetHighlightMaterial();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> mesh = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuild> m_build = nullptr;

	virtual void BeginPlay() override;
	
};
