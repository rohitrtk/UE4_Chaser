// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChaserGameMode.h"
#include "ChaserCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "PickupSpawner.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"


AChaserGameMode::AChaserGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	this->MaxPickups = 5;
}


void AChaserGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartRoundWait();
}


void AChaserGameMode::StartRoundWait()
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, "Round Wait Ticked!");

	this->CurrentGameState = EGameState::GS_RoundWait;

	for (TActorIterator<AActor> It(this->GetWorld(), APickupSpawner::StaticClass()); It; ++It)
	{
		APickupSpawner* spawner = Cast<APickupSpawner>(*It);
		if (spawner) this->Spawners.Add(spawner);
	}

	this->GetWorldTimerManager().SetTimer(this->_roundTimer, this, &AChaserGameMode::StartRoundPlay, RoundWaitTime);
}


void AChaserGameMode::StartRoundPlay()
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, "Round Play Ticked!");

	this->CurrentGameState = EGameState::GS_RoundPlay;
	this->GetWorldTimerManager().ClearTimer(_roundTimer);

	Spawn();
	this->GetWorldTimerManager().SetTimer(this->_spawnTimer, this, &AChaserGameMode::Spawn, 1.f, true);
}


void AChaserGameMode::Spawn()
{
	if (Spawners[0]->PickupsSpawned < MaxPickups)
	{
		Spawners[0]->SpawnPickup();
	}
	else
	{
		this->GetWorldTimerManager().ClearTimer(this->_spawnTimer);

		StartRoundWait();
	
		Spawners[0]->PickupsSpawned = 0;
	}
}

