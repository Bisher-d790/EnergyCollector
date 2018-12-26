// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "EnergyCollector.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Activate pickup
	bIsActive = true;

	// Creates Static Mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns Pickup state
bool APickup::IsActive() {
	return bIsActive;
}

// Changes Pickup state
void APickup::SetActive(bool newPickupState) {
	bIsActive = newPickupState;
}

void APickup::WasCollected_Implementation() {
	// Log a debug message
	FString PickupDebugName = GetName();
	UE_LOG(LogClass, Log, TEXT("You have cellected %s"), *PickupDebugName);
}
