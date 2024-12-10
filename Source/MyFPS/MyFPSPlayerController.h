// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyFPSPlayerController.generated.h"

class UGameOverWidget;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class MYFPS_API AMyFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameOverWidget> BP_GameOverWidget;
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

public:
	/** Show the Game Over Widget */
	void ShowGameOverWidget(int32 Score);

	/** Hide the Game Over Widget */
	void HideGameOverWidget();
	
	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

private:
	UPROPERTY()
	UGameOverWidget* GameOverWidget;
};
