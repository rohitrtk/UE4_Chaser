// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChaserGameMode.h"
#include "ChaserCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "PickupSpawner.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Pickup.h"


AChaserGameMode::AChaserGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AChaserGameMode::BeginPlay()
{
	Super::BeginPlay();

	this->MaxPickups = 5;
	this->GameTime = 60.f;
	//this->CurrentGameState = EGameState::GS_MainMenu;
}


void AChaserGameMode::StartRoundWait()
{
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, "Round Wait Ticked!");

	this->CurrentGameState = EGameState::GS_RoundWait;

	for (TActorIterator<AActor> It(this->GetWorld(), APickupSpawner::StaticClass()); It; ++It)
	{
		APickupSpawner* spawner = Cast<APickupSpawner>(*It);
		if (spawner && !Spawners.Contains(spawner))
		{
			this->Spawners.Add(spawner);
		}
	}

	this->GetWorldTimerManager().SetTimer(this->_roundTimer, this, &AChaserGameMode::StartRoundPlay, RoundWaitTime, false);
}


void AChaserGameMode::StartRoundPlay()
{
	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, "Round Play Ticked!");

	this->CurrentGameState = EGameState::GS_RoundPlay;

	Spawn();
	this->GetWorldTimerManager().SetTimer(this->_spawnTimer, this, &AChaserGameMode::Spawn, 1.f, true);

	this->GetWorldTimerManager().SetTimer(this->_gameOverTimer, this, &AChaserGameMode::GameTimerElapsed, 1.f, true);
}


void AChaserGameMode::Spawn()
{
	if (!Spawners[0])
	{
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Purple, "Could not spawn pickup!");
		return;
	}

	Spawners[0]->SpawnPickup();

	/*
	if (Spawners[0]->PickupsSpawned < MaxPickups)
	{
		Spawners[0]->SpawnPickup();
	}
	else
	{
		this->GetWorldTimerManager().ClearTimer(this->_spawnTimer);

		StartRoundWait();

		Spawners[0]->PickupsSpawned = 0;
	} */
}


void AChaserGameMode::CleanWorld()
{
	for (TActorIterator<AActor> It(this->GetWorld(), APickup::StaticClass()); It; ++It)
	{
		APickup* pickup = Cast<APickup>(*It);
		if (pickup)
		{
			pickup->DestroyActor();
		}
	}
}


void AChaserGameMode::GameTimerElapsed()
{
	if (GameTime <= 0)
	{
		this->GetWorldTimerManager().ClearTimer(_gameOverTimer);

		this->GetWorldTimerManager().ClearTimer(_spawnTimer);

		this->CurrentGameState = EGameState::GS_GameOver;

		CleanWorld();

		DisplayGameOverScreen();

		return;
	}

	GameTime -= 1;
}

