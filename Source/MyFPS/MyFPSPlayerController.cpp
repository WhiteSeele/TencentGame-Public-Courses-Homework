// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameOverWidget.h"

void AMyFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AMyFPSPlayerController::ShowGameOverWidget(int32 Score)
{
	SetPause(true);
	//更新到 UIOnly 的输入模式
	SetInputMode(FInputModeUIOnly());
	//显示光标
	bShowMouseCursor = true;
	//创建 GameOverWidget，传递给拥有者玩家
	GameOverWidget = CreateWidget<UGameOverWidget>(this, BP_GameOverWidget);
	GameOverWidget->ResetScore(Score);
	GameOverWidget->AddToViewport();
}

void AMyFPSPlayerController::HideGameOverWidget()
{
	//从屏幕上移除 GameOverWidget
	GameOverWidget->RemoveFromParent();
	GameOverWidget -> Destruct();

	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
