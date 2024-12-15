// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginLevelController.generated.h"

class UUserLoginWidget;
/**
 * 
 */
UCLASS()
class MYFPS_API ALoginLevelController : public APlayerController
{
	GENERATED_BODY()

public:
	ALoginLevelController();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UUserLoginWidget* UserLoginWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserLoginWidget> UserLoginWidgetClass;
};
