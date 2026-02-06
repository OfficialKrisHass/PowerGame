#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include <Logging/LogMacros.h>

#include "Core/Core.h"

#include "BuildModeManager.generated.h"

// Player

class AMainPlayerCharacter;
class AMainPlayerController;

// Building

class UBuild;

class ABuildGhost;
class ABuildInstance;

// UE Components

class UCameraComponent;

// UE Input

class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogBuilding, Log, All);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POWERGAME_API UBuildModeManager : public UActorComponent {

	GENERATED_BODY()

public:
	UBuildModeManager();

	UFUNCTION(BlueprintCallable)
	void StartBuildMode();
	UFUNCTION(BlueprintCallable)
	void EndBuildMode();

protected:
	UPROPERTY(VisibleAnywhere)
	bool buildModeActive = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBuild> testBuild = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuildInstance> buildInstanceClass = nullptr;

	// Build Ghost

	UPROPERTY(EditDefaultsOnly, Category = "Build Ghost")
	TSubclassOf<ABuildGhost> buildGhostClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "Build Ghost")
	float buildGhostRange = 5000.0f;

	// Input

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> buildModeIMC = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> endBuildModeAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> buildAction = nullptr;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<ABuildGhost> m_buildGhost = nullptr;

	// References

	UPROPERTY()
	TObjectPtr<AMainPlayerCharacter> m_character = nullptr;
	UPROPERTY()
	TObjectPtr<AMainPlayerController> m_controller = nullptr;
	UPROPERTY()
	TObjectPtr<UCameraComponent> m_camera = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Build();

	void SpawnBuildGhost();
	
};
