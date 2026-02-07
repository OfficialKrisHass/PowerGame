#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Character.h>
#include <Logging/LogMacros.h>

#include "Core/Core.h"

#include "MainPlayerCharacter.generated.h"

class UConstructionModeManager;

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

	inline UCameraComponent* GetCamera() const { return camera; }
	inline USkeletalMeshComponent* GetArmMesh() const { return armMesh; }

protected:
	// Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> armMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UConstructionModeManager> constructionModeManager = nullptr;

	//
	// Input
	//

	// Movement

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> moveAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> lookAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> jumpAction = nullptr;

	// Mode switching

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> selectBuildToolAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> selectDeconstructToolAction = nullptr;

private:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	
	virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

};