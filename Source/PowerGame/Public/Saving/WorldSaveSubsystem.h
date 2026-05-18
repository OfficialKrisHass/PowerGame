#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Logging/LogMacros.h>

#include "Core/Core.h"

#include "WorldSaveSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSaveSubsystem, Log, All)

UCLASS()
class POWERGAME_API UWorldSaveSubsystem : public UGameInstanceSubsystem {

	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	UFUNCTION()
	void SaveWorld();
	UFUNCTION()
	void LoadWorld();

private:
	UFUNCTION()
	void SavingFinished(const FString& slotName, int32 userIndex, bool success);
	UFUNCTION()
	void LoadingFinished(const FString& slotName, int32 userIndex, USaveGame* loadedSave);

};