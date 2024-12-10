// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameTimerMode.generated.h"

/**
 * 
 */
UCLASS()
class MYFPS_API AFPSTimerMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSTimerMode();

protected:
	virtual void BeginPlay() override;

private:
	void EndGame() const;
	void SelectImportantTargets();
	
	FTimerHandle GameEndTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Game Timer")
	float GameDuration = 30.0f;       // Duration of the game in seconds

	UPROPERTY(EditAnywhere, Category = "Game Rules")
	uint32 NumberofTargets;

	TArray<AActor*> TargetBlocks;
};
