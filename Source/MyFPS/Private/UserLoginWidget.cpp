// Fill out your copyright notice in the Description page of Project Settings.


#include "UserLoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UUserLoginWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (LoginButton != nullptr)
	{
		LoginButton->OnClicked.AddDynamic(this, &UUserLoginWidget::OnLoginClicked);
	}
	if (QuitButton != nullptr)
	{
		QuitButton->OnClicked.AddDynamic(this, &UUserLoginWidget::OnQuitClicked);
	}
	if (PasswordField != nullptr)
	{
		PasswordField->SetIsPassword(true);
	}
}

void UUserLoginWidget::OnLoginClicked()
{
	if (UsernameField != nullptr)
	{
		UsernameField -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (PasswordField != nullptr)
	{
		PasswordField -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (LoginButton != nullptr)
	{
		LoginButton -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (QuitButton != nullptr)
	{
		QuitButton -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (WelcomeText != nullptr)
	{
		WelcomeText -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (UsernameText != nullptr)
	{
		UsernameText -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (PasswordText != nullptr)
	{
		PasswordText -> SetVisibility(ESlateVisibility::Hidden);
	}
	if (LoginProgressBar != nullptr)
	{
		LoginProgressBar -> SetVisibility(ESlateVisibility::Visible);
	}

	GetWorld()->GetTimerManager().SetTimer(ProgressBarTimerHandle, this,
		&UUserLoginWidget::UpdateProgressBar, 0.1f, true);
}

void UUserLoginWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UUserLoginWidget::UpdateProgressBar()
{
	if (LoginProgressBar != nullptr)
	{
		LoginProgressBar -> SetPercent(LoginProgressBar->GetPercent() + 0.01f);
		if (LoginProgressBar->GetPercent() >= 1.0f)
		{
			GetWorld()->GetTimerManager().ClearTimer(ProgressBarTimerHandle);
			LoadLevel();
		}
	}
}

void UUserLoginWidget::LoadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonMap");

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}