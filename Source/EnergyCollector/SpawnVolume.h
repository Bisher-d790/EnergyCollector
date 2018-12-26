// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class ENERGYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawnable Object
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	// Min spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeLow;

	// Max spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeHigh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns WhereToSpawn Box Component
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; };

	// Finds arandom point with in the spawn volume
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	// Activates the spawning volume
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void SetSpawningActive(bool bShouldSpawn);

private:
	// Box component to specify where to spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* WhereToSpawn;

	// Spawn Object
	void SpawnPickup();

	// Current Spawn delay
	float SpawnDelay;



};
