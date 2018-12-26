// Fill out your copyright notice in the Description page of Project Settings.

#include "Battery.h"
#include "EnergyCollector.h"
#include "Components/StaticMeshComponent.h"




	// Sets default values for this actor's properties
ABattery::ABattery() {
	GetMesh()->SetSimulatePhysics(true);

	// Base Battery Power
	BatteryPower = 150.0f;
}


void ABattery::WasCollected_Implementation() {
	// Call parent behaviour
	Super::WasCollected_Implementation();

	// Destroy battery pickup
	Destroy();
}

/** Returns Battery power*/
float ABattery::GetPower() {
	return BatteryPower;
}