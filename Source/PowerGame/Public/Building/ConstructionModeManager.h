#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include <Logging/LogMacros.h>

#include "Core/Core.h"

#include "ConstructionModeManager.generated.h"

// Player

class AMainPlayerCharacter;
class AMainPlayerController;

// Building

class UBuild;

class ABuildGhost;
class ABuildInstance;

// UI

class UBuildMenu;

// UE Components

class UCameraComponent;

// UE Input

class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogBuilding, Log, All);

UENUM(BlueprintType)
enum class EConstructionTool : uint8 {

	None = 0 UMETA(DisplayName = "None"),
	BuildTool UMETA(DisplayName = "Build Tool"),
	DeconstructTool UMETA(DisplayName = "Deconstruct tool"),

};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POWERGAME_API UConstructionModeManager : public UActorComponent {

	GENERATED_BODY()

public:
	UConstructionModeManager();

	// Entering/Leaving Construction mode

	UFUNCTION(BlueprintCallable)
	inline void EnterConstructionMode(EConstructionTool toolToSelect) {

		switch (toolToSelect) {

		case EConstructionTool::None: ExitConstructionMode(); break;
		case EConstructionTool::BuildTool: SelectBuildTool(); break;
		case EConstructionTool::DeconstructTool: SelectDeconstructTool(); break;

		}

	}

	UFUNCTION(BlueprintCallable)
	void SelectBuildTool();
	UFUNCTION(BlueprintCallable)
	void SelectDeconstructTool();
	UFUNCTION(BlueprintCallable)
	void ExitConstructionMode();

	UFUNCTION(BlueprintCallable)
	void SelectBuild(UBuild* build);

	// Grid snap

	UFUNCTION(BlueprintCallable)
	void ToggleGridSnap();

	// UI

	UFUNCTION(BlueprintCallable)
	void BindUI(UBuildMenu* buildMenu);

	// Getters

	UFUNCTION(BlueprintCallable)
	inline UBuildMenu* GetBuildMenu() const { return m_buildMenu; }

protected:
	UPROPERTY(VisibleAnywhere)
	EConstructionTool tool = EConstructionTool::None;
	UPROPERTY()
	TObjectPtr<UBuild> selectedBuild = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UBuild>> availableBuilds;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuildInstance> buildInstanceClass = nullptr;

	// Build Ghost

	UPROPERTY(EditDefaultsOnly, Category = "Build tool")
	TSubclassOf<ABuildGhost> buildGhostClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "Build tool")
	float buildToolRange = 5000.0f;

	UPROPERTY(EditAnywhere, Category = "Build tool")
	TObjectPtr<UInputAction> selectBuildToolAction = nullptr;

	// Building grid

	UPROPERTY(VisibleAnywhere, Category = "Building grid")
	bool gridSnap = false;
	UPROPERTY(EditAnywhere, Category = "Building grid");
	float gridSize = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Building grid")
	TObjectPtr<UInputAction> toggleGridSnapAction = nullptr;

	// Deconstruct mode

	UPROPERTY(VisibleAnywhere, Category = "Deconstruct tool")
	TObjectPtr<ABuildInstance> highlightedBuildInstance = nullptr;
	UPROPERTY(EditAnywhere, Category = "Deconstruct tool")
	TObjectPtr<UMaterialInterface> deconstructHighlightMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = "Deconstruct tool")
	TObjectPtr<UInputAction> selectDeconstructToolAction = nullptr;

	// Input

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> constructionModeIMC = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> confirmAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> exitAction = nullptr;

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

	// UI

	UPROPERTY()
	TObjectPtr<UBuildMenu> m_buildMenu = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Confirm();
	void ConfirmBuildTool();
	void ConfirmDeconstructTool();

	void SpawnBuildGhost();

	void HandleBuildTool();
	void HandleDeconstructTool();
	
};
