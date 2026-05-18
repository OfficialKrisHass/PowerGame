#include "Saving/WorldSaveSubsystem.h"
#include "Saving/WorldSaveData.h"
#include "Saving/BuildingSaveData.h"

#include "Player/MainPlayerCharacter.h"

#include "Building/Instances/BuildInstance.h"

#include <Kismet/GameplayStatics.h>

#include <EngineUtils.h>
#include <StructUtils.h>

DEFINE_LOG_CATEGORY(LogSaveSubsystem)

void UWorldSaveSubsystem::Initialize(FSubsystemCollectionBase& collection) {

	Super::Initialize(collection);

}
void UWorldSaveSubsystem::Deinitialize() {

	Super::Deinitialize();

}

void UWorldSaveSubsystem::SaveWorld() {

	// Setup the save data object and delegate

	UWorldSaveData* saveData = Cast<UWorldSaveData>(UGameplayStatics::CreateSaveGameObject(UWorldSaveData::StaticClass()));
	PW_ASSERT(saveData != nullptr, LogSaveSubsystem, TEXT("Could not create UWorldSaveData save object."));

	FAsyncSaveGameToSlotDelegate saveDelegate;
	saveDelegate.BindUObject(this, &UWorldSaveSubsystem::SavingFinished);

	// Save player data

	AMainPlayerCharacter* character = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PW_ASSERT(character != nullptr, LogSaveSubsystem, TEXT("Could not get AMainPlayerCharacter from UGameplayStatistics::GetPlayerCharacter()."));

	saveData->playerPosition = character->GetActorLocation();
	saveData->playerRotation = character->GetActorRotation();

	// Save buildings data

	for (TActorIterator<ABuildInstance> it(GetWorld()); it; ++it) {

		FInstancedStruct entry;
		ABuildInstance* buildInstance = *it;

		buildInstance->SerializeSaveData(&entry);
		saveData->buildings.Add(entry);

	}

	// Save the data to an actual save slot

	UGameplayStatics::AsyncSaveGameToSlot(saveData, "SaveSlot1", 0, saveDelegate);
	
}
void UWorldSaveSubsystem::LoadWorld() {

	FAsyncLoadGameFromSlotDelegate loadDelegate;
	loadDelegate.BindUObject(this, &UWorldSaveSubsystem::LoadingFinished);

	UGameplayStatics::AsyncLoadGameFromSlot("SaveSlot1", 0, loadDelegate);

}

void UWorldSaveSubsystem::SavingFinished(const FString& slotName, int32 userIndex, bool success) {

	PW_LOG(LogSaveSubsystem, TEXT("Saving finished into slot '%s'"), *slotName);

}
void UWorldSaveSubsystem::LoadingFinished(const FString& slotName, const int32 userIndex, USaveGame* loadedSaveData) {

	UWorldSaveData* saveData = Cast<UWorldSaveData>(loadedSaveData);
	PW_ASSERT(saveData != nullptr, LogSaveSubsystem, TEXT("Could not cast USaveGame to UWorldSaveData when loading save slot '%s'"), *slotName);

	UWorld* world = GetWorld();
	PW_ASSERT(world != nullptr, LogSaveSubsystem, TEXT("Could not get world."));

	// Load player data

	AMainPlayerCharacter* character = Cast<AMainPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(world, 0));
	PW_ASSERT(character != nullptr, LogSaveSubsystem, TEXT("Could not get AMainPlayerCharacter from UGameplayStatistics::GetPlayerCharacter()."));

	character->SetActorLocationAndRotation(saveData->playerPosition, saveData->playerRotation);
	character->GetController()->SetControlRotation(saveData->playerRotation);

	// Load buildings

	for (const FInstancedStruct& data : saveData->buildings) {

		PW_ASSERT(data.GetScriptStruct()->IsChildOf(FBuildingSaveData::StaticStruct()), LogSaveSubsystem, TEXT("Saved FInstancedStructis not of type FBuildingSaveData."));
		const FBuildingSaveData& buildingSaveData = data.Get<FBuildingSaveData>();

		ABuildInstance* buildInstance = world->SpawnActor<ABuildInstance>(buildingSaveData.buildClass, buildingSaveData.transform);
		PW_ASSERT(buildInstance != nullptr, LogSaveSubsystem, TEXT("Could not spawn ABuildInstance actor of class '%s'"), *GetNameSafe(buildingSaveData.buildClass));

		buildInstance->DeserializeSaveData(data);

	}

}