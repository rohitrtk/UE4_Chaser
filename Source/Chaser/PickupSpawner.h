// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

class USceneComponent;
class UBoxComponent;
class APickup;

UCLASS()
class CHASER_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* PickupSpawners Scene Component */
	UPROPERTY(VisibleAnywhere, Category = "Scene Component")
	USceneComponent* SceneComponent;

	/* PickupSpawners Box Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComponent;

	/* The time to wait before spawning a pickup */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SpawnTime;

	/* Spawn actor */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APickup> SpawnActor;

	/* Spawns the spawn actor */
	UFUNCTION(BlueprintCallable)
	void SpawnPickup();

	/* Number of Pickups spawned so far */
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	int32 PickupsSpawned;
};
