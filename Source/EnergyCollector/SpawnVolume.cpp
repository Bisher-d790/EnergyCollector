// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "EnergyCollector.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creates WhereToSpawn Box Component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	// Set spawn delay range
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Get a random point in the spawn volume
FVector ASpawnVolume::GetRandomPointInVolume() {
	FVector VolumeOrigin = WhereToSpawn->Bounds.Origin;
	FVector VolumeExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(VolumeOrigin, VolumeExtent);
}

// Activates the spawning volume
void ASpawnVolume::SetSpawningActive(bool bShouldSpawn) {
	if (bShouldSpawn) {
		// Sets the timer on spawn pickup
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else {
		// Clears the timer on spawn pickup
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

// Spawn Object
void ASpawnVolume::SpawnPickup() {
	// Check for spawnable object if set
	if (WhatToSpawn != NULL) {

		// Check for world
		UWorld* World = GetWorld();
		if (World) {

			// Set Spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get spawn point location
			FVector SpawnLocation = GetRandomPointInVolume();

			// Get spawn rotation
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			// Spawn object
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}
	}
}