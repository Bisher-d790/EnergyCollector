// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EnergyCollectorGameMode.h"
#include "EnergyCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine.h"
#include "SpawnVolume.h"

AEnergyCollectorGameMode::AEnergyCollectorGameMode()
{
	// Allowing Ticking
	PrimaryActorTick.bCanEverTick = true;
	// Base Decay Rate
	DecayRate = 0.01f;

}

void AEnergyCollectorGameMode::BeginPlay() {
	Super::BeginPlay();

	// Find All Spawn Volumes
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors) {
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor) {
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(EBatteryPlayState::EPlaying);

	// Get My Character
	AEnergyCollectorCharacter* MyCharacter = Cast<AEnergyCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Set Power To Win
	if (MyCharacter) {
		PowerToWin = (MyCharacter->GetInitialPower()) * 1.25f;
	}

	// Create HUD
	if (HUDWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}

}

void AEnergyCollectorGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Get character, and check if it's the current character
	AEnergyCollectorCharacter* MyCharacter = Cast<AEnergyCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {
		// if player's Power > Win Score 
		if (MyCharacter->GetCurrentPower() > GetPowerToWin()) {
			SetCurrentState(EBatteryPlayState::EWon);
		}
		// else if current power is positive
		else if (MyCharacter->GetCurrentPower() > 0) {
			// Decrease power with decay rate
			MyCharacter->UpdatePower(-1 * DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		}
		// else the player is out of energy
		else {
			SetCurrentState(EBatteryPlayState::EGameover);
		}
	}
}

float AEnergyCollectorGameMode::GetPowerToWin() const {
	return PowerToWin;
}

EBatteryPlayState AEnergyCollectorGameMode::GetCurrentState() const {
	return CurrentState;
}

void AEnergyCollectorGameMode::SetCurrentState(EBatteryPlayState NewState) {
	// Sets Current State
	CurrentState = NewState;

	// Handles the new State
	HandleNewState(CurrentState);
}

void AEnergyCollectorGameMode::HandleNewState(EBatteryPlayState NewState) {
	switch (CurrentState)
	{
	case EBatteryPlayState::EPlaying:
		// Game is playing
	{
		//Spawn Volumes Active
		for (ASpawnVolume* SpawnVolume : SpawnVolumeActors) {
			SpawnVolume->SetSpawningActive(true);
		}
	}
	break;

	case EBatteryPlayState::EWon:
		// Game Won
	{
		//Spawn Volumes Inactive
		for (ASpawnVolume* SpawnVolume : SpawnVolumeActors) {
			SpawnVolume->SetSpawningActive(false);
		}
	}
	break;

	case EBatteryPlayState::EGameover:
		// Game Lost
	{
		// Spawn Volumes Inactive
		for (ASpawnVolume* SpawnVolume : SpawnVolumeActors) {
			SpawnVolume->SetSpawningActive(false);
		}
		// Block Input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController) {
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		// Ragdoll the Character
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter) {
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;

	case EBatteryPlayState::EUnknown:
		// Default/Unknown state
		// Do Nothing
		break;
	}
}
