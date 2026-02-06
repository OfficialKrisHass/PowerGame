#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "BuildGhost.generated.h"

class UBuild;

UCLASS()
class POWERGAME_API ABuildGhost : public AActor {

	GENERATED_BODY()
	
public:
	ABuildGhost();

	UFUNCTION(BlueprintCallable)
	void SetBuild(UBuild* build);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> mesh = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuild> m_build = nullptr;

	virtual void BeginPlay() override;
	
};