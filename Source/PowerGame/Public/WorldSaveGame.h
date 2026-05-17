#pragma once

#include <CoreMinimal.h>
#include <GameFramework/SaveGame.h>

#include "WorldSaveGame.generated.h"

UCLASS()
class POWERGAME_API UWorldSaveGame : public USaveGame {

	GENERATED_BODY()
	
public:
	UWorldSaveGame();
	
	// Slot data

	UPROPERTY(VisibleAnywhere, Category = "Slot data")
	FString slotName;
	UPROPERTY(VisibleAnywhere, Category = "Slot data")
	uint32 userIndex = 0;

	// Temp.

	UPROPERTY(VisibleAnywhere)
	FString test;

};