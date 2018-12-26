// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnergyCollectorGameMode.generated.h"

// ENUM to store current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8 {
	EPlaying,
	EGameover,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class AEnergyCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEnergyCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	// Returns Power to Win
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetPowerToWin() const;

	virtual void BeginPlay() override;

	// Returns the current play state
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	// Sets the current play state
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	// Rate of Power Decay for the player
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float DecayRate;

	// Power needed to win
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float PowerToWin;

	// Widget class for HUD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	// the instance of HUD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		UUserWidget* CurrentWidget;

private:
	// Store the current State
	EBatteryPlayState CurrentState;

	// Keeps track of Spawn Volumes
	TArray<class ASpawnVolume*> SpawnVolumeActors;

	// Handles functions that togle after new playstate
	void HandleNewState(EBatteryPlayState NewState);
};



