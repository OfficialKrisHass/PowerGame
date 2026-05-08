#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Character.h>
#include <Logging/LogMacros.h>

#include "Core/Core.h"

#include "MainPlayerCharacter.generated.h"

class UConstructionModeManager;

class ABuildInstance;

// UI

class UNetworkVisualizer;

// UE Components

class USkeletalMeshComponent;
class UCameraComponent;
class UInputComponent;

// UE Input

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);

UCLASS(config=Game)
class POWERGAME_API AMainPlayerCharacter : public ACharacter {

	GENERATED_BODY()

public:
	AMainPlayerCharacter();

	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	inline void BindUI(UNetworkVisualizer* visualizer) { m_networkVisualizer = visualizer; }

	UFUNCTION(BlueprintCallable)
	inline UCameraComponent* GetCamera() const { return camera; }
	UFUNCTION(BlueprintCallable)
	inline USkeletalMeshComponent* GetArmMesh() const { return armMesh; }
	UFUNCTION(BlueprintCallable)
	inline UConstructionModeManager* GetConstructionModeManager() const { return constructionModeManager; }

protected:
	// Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> armMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UConstructionModeManager> constructionModeManager = nullptr;

	//
	// Interactions
	//

	UPROPERTY(EditAnywhere, Category = "Interactions")
	float interactionRange = 50.0f;
	UPROPERTY(VisibleAnywhere, Category = "Interactions")
	TObjectPtr<ABuildInstance> targetInteractible = nullptr;

	//
	// Input
	//

	// Movement

	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	TObjectPtr<UInputAction> moveAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	TObjectPtr<UInputAction> lookAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	TObjectPtr<UInputAction> jumpAction = nullptr;

	// Interactions

	UPROPERTY(EditAnywhere, Category = "Input|Interactions")
	TObjectPtr<UInputAction> interactAction = nullptr;

	// Mode switching

	UPROPERTY(EditAnywhere, Category = "Input|Modes")
	TObjectPtr<UInputAction> selectBuildToolAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input|Modes")
	TObjectPtr<UInputAction> selectDeconstructToolAction = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UNetworkVisualizer> m_networkVisualizer = nullptr;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);

	void Interact(const FInputActionValue& value);
	
	virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

};