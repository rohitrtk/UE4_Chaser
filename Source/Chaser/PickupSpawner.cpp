// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSpawner.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "kismet/GameplayStatics.h"
#include "kismet/KismetMathLibrary.h"
#include "ChaserGameMode.h"
#include "Pickup.h"
#include "Engine/GameEngine.h"


APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	this->RootComponent = this->SceneComponent;

	this->BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
	this->BoxComponent->SetupAttachment(this->SceneComponent);

	this->SpawnTime = 3.f;
	this->PickupsSpawned = 0;
}


void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
}


void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APickupSpawner::SpawnPickup()
{
	UWorld* world = this->GetWorld();
	AChaserGameMode* currentGamemode = Cast<AChaserGameMode>(world->GetAuthGameMode());

	FVector spawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(this->GetActorLocation(), this->BoxComponent->GetScaledBoxExtent());
	FRotator rotator;

	if (this->SpawnActor)
	{
		world->SpawnActor<APickup>(this->SpawnActor, spawnLocation, rotator);

		this->PickupsSpawned++;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, "Pickup doesn't exist!");
	}
}

