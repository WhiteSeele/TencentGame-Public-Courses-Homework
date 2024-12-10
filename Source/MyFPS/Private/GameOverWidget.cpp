// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyFPS/MyFPSPlayerController.h"

void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (RestartButton != nullptr)
	{
		RestartButton -> OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartClicked);
	}
	if (QuitButton != nullptr)
	{
		QuitButton -> OnClicked.AddDynamic(this, &UGameOverWidget::OnQuitClicked);
	}
}

void UGameOverWidget::OnQuitClicked()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0) -> ConsoleCommand("quit");
}

void UGameOverWidget::OnRestartClicked()
{
	AMyFPSPlayerController* PlayerController = Cast<AMyFPSPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController -> HideGameOverWidget();
	}
	FString CurrentLevelName = GetWorld() -> GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld() -> StreamingLevelsPrefix);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}

void UGameOverWidget::ResetScore(int32 Score)
{
	UserScore = Score;
	if (ScoreEcho != nullptr)
	{
		ScoreEcho -> SetText(FText::FromString(FString::Printf(TEXT("You totally get %d scores"), UserScore)));
	}
}



