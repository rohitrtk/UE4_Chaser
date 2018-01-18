// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChaserGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	GS_RoundWait	UMETA(DisplayName = "Round Wait"),
	GS_RoundPlay	UMETA(DisplayName = "Round Play"),
	GS_MainMenu		UMETA(DisplayName = "Menu")
};

class APickupSpawner;

UCLASS(minimalapi)
class AChaserGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChaserGameMode();

	/** Called on play button **/
	void BeginPlay();

	/** Games current game state **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	EGameState CurrentGameState;

	/** Time to wait before starting the next round **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float RoundWaitTime = 3.f;

	/** Sets the game state to round wait **/
	UFUNCTION(BlueprintCallable)
	void StartRoundWait();

	/** Sets the game state to round play **/
	UFUNCTION(BlueprintCallable)
	void StartRoundPlay();

	/** Spawns pickups **/
	UFUNCTION(BlueprintCallable)
	void Spawn();

	/** Array of APickupSpawner's in the world **/
	TArray<APickupSpawner*> Spawners;

	/** Maximum pickups to spawn per round **/
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	int32 MaxPickups;

private:

	FTimerHandle _roundTimer;
	FTimerHandle _spawnTimer;
};

