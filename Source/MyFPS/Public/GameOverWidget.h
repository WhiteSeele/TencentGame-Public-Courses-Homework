// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "GameOverWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class MYFPS_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ResetScore(int32 Score);
	
protected:
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnQuitClicked();

	virtual void NativeOnInitialized() override;
	
public:
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* ScoreEcho;

private:
	int32 UserScore;
};
