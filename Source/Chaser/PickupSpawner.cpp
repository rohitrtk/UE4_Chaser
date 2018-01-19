// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSpawner.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "kismet/GameplayStatics.h"
#include "kismet/KismetMathLibrary.h"
#include "ChaserGameMode.h"
#include "Pickup.h"
#include "Engine/GameEngine.h"

// Sets default values
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

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to spawn an APickup actor
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
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, "Pickup doesn't exist!");
	}
}

