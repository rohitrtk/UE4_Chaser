// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChaserCharacter.h"
#include "Engine/Engine.h"


APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	this->RootComponent = this->MeshComponent;

	this->SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	this->SphereCollider->SetWorldScale3D(this->MeshComponent->GetComponentScale());
	this->SphereCollider->SetupAttachment(this->MeshComponent);

	this->SphereCollider->SetMassOverrideInKg(TEXT("NAME_None"), 100000.f);
}


void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	this->SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APickup::Overlap);

	this->LifeSpan = 7.f;

	// Ghetto actor lifespan
	GetWorldTimerManager().SetTimer(this->_lifeSpanTimerHandle, this, &APickup::DestroyActor, LifeSpan, false);
}


void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APickup::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComponent)
	{
		AChaserCharacter* character = Cast<AChaserCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

		if (character)
		{
			this->_touchedByPlayer = true;

			character->IncrementScore(1);
			character->SetMoveSpeed(character->Score);
			DestroyActor();
		}
	}
}


void APickup::DestroyActor()
{
	if(!_touchedByPlayer) UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), BoomEffect, this->GetActorLocation());
	else UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), CoolEffect, this->GetActorLocation());

	Destroy();
}

