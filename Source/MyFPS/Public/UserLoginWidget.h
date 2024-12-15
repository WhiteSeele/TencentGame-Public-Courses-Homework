// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserLoginWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class MYFPS_API UUserLoginWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void OnLoginClicked();

	UFUNCTION()
	void OnQuitClicked();

	UFUNCTION()
	void UpdateProgressBar();

	UFUNCTION()
	void LoadLevel();

	virtual void NativeOnInitialized() override;
	
public:
	UPROPERTY(meta=(BindWidgetOptional))
	UButton* LoginButton;

	UPROPERTY(meta=(BindWidgetOptional))
	UButton* QuitButton;

	UPROPERTY(meta=(BindWidgetOptional))
	UEditableTextBox* UsernameField;

	UPROPERTY(meta=(BindWidgetOptional))
	UEditableTextBox* PasswordField;

	UPROPERTY(meta=(BindWidgetOptional))
	UProgressBar* LoginProgressBar;

	UPROPERTY(meta=(BindWidgetOptional))
	UTextBlock* WelcomeText;

	UPROPERTY(meta=(BindWidgetOptional))
	UTextBlock* UsernameText;

	UPROPERTY(meta=(BindWidgetOptional))
	UTextBlock* PasswordText;

private:
	FTimerHandle ProgressBarTimerHandle;
};
