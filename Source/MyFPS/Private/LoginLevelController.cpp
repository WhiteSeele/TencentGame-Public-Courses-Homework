// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginLevelController.h"
#include "UserLoginWidget.h"
#include "Blueprint/UserWidget.h"

void ALoginLevelController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UserLoginWidgetClass != nullptr)
	{
		UserLoginWidget = CreateWidget<UUserLoginWidget>(this, UserLoginWidgetClass);
		if (UserLoginWidget != nullptr)
		{
			UserLoginWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}