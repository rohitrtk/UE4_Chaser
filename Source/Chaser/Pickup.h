// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UBoxComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class CHASER_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** This actors statics mesh component **/
	UPROPERTY(VisibleAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* MeshComponent;

	/** This actors sphere collider **/
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* SphereCollider;

	/** This actors particle emitter if not touched by a player; displayed on death **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	UParticleSystem* BoomEffect;

	/** This actors particle emitter if touched by a player; displayed on death **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	UParticleSystem* CoolEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	float LifeSpan;

	UFUNCTION(BlueprintCallable)
	/** Calls Destroy() but spawns a particle effect before death **/
	void DestroyActor();

	/** Called upon actor overlap **/
	UFUNCTION()
	void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	
	FTimerHandle _lifeSpanTimerHandle;

	bool _touchedByPlayer = false;
};

