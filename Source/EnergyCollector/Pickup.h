// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ENERGYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Pickup isActive
	bool bIsActive;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns Pickup state
	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool IsActive();

	// Changes Pickup state
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool newPickupState);

	// Return static mesh component
	FORCEINLINE class UStaticMeshComponent* GetMesh() { return PickupMesh; }

	// Function to call when collected
	UFUNCTION(BlueprintNativeEvent)
		void WasCollected();
	virtual void WasCollected_Implementation();

private:
	// Component to hold mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PickupMesh;



};
