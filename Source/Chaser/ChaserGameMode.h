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
	GS_MainMenu		UMETA(DisplayName = "Menu"),
	GS_GameOver		UMETA(DisplayName = "Game Over")
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
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TArray<APickupSpawner*> Spawners;

	/** Maximum pickups to spawn per round **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 MaxPickups;

	/* Time in seconds before calling GamerTimerElapsed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	float GameTime;

	/* Called when the game timer has been elapsed */
	UFUNCTION(BlueprintCallable)
	void GameTimerElapsed();

	/* Called to end the game and show the user their score */
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayGameOverScreen();

private:

	FTimerHandle _roundTimer;
	FTimerHandle _spawnTimer;
	FTimerHandle _gameOverTimer;
};

