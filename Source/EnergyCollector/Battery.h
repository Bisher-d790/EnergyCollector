// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Battery.generated.h"

/**
 * 
 */
UCLASS()
class ENERGYCOLLECTOR_API ABattery : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABattery();
	
	// Override WasColleceted Implementation Function 
	void WasCollected_Implementation() override;

	/** Returns Battery power*/
	float GetPower();

protected:
	// Set amount of power for battery
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (Blueprint = "true"))
	float BatteryPower;
};
