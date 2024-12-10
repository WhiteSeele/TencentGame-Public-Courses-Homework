// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameTimerMode.h"

#include "BlockHitCallbackComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyFPS/MyFPSCharacter.h"
#include "MyFPS/MyFPSPlayerController.h"


AFPSTimerMode::AFPSTimerMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonPlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	GameDuration = 15.0f;
	NumberofTargets = 6;
}

void AFPSTimerMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(GameEndTimerHandle, this, &AFPSTimerMode::EndGame, GameDuration, false);
	SelectImportantTargets();
}

void AFPSTimerMode::EndGame() const
{
	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++ It)
	{
		if(AMyFPSPlayerController* PlayerController = Cast<AMyFPSPlayerController>(*It))
		{
			if(AMyFPSCharacter* Player = Cast<AMyFPSCharacter>(PlayerController->GetPawn()))
			{
				int32 Score = Player -> GetScore();
				PlayerController -> ShowGameOverWidget(Score);
			}
		}
	}
}

void AFPSTimerMode::SelectImportantTargets()
{
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

	for(AActor* Actor: AllActors)
	{
		if(Actor -> FindComponentByClass<UBlockHitCallbackComponent>())
		{
			TargetBlocks.Add(Actor);
		}
	}
	if(TargetBlocks.Num() > 0)
	{
		for(uint32 i = 0; i < NumberofTargets; ++i)
		{
			int32 RandomIndex = FMath::RandRange(0, TargetBlocks.Num() - 1);
			if(UBlockHitCallbackComponent* BlockHitCallbackComponent = Cast<UBlockHitCallbackComponent>(TargetBlocks[RandomIndex] -> FindComponentByClass(UBlockHitCallbackComponent::StaticClass())))
			{
				UMaterialInterface* TargetMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/FPWeapon/Materials/M_Gold.M_Gold'"));
				BlockHitCallbackComponent -> SetTargetMaterial(TargetMaterial);
				BlockHitCallbackComponent -> SetIsImportantTarget(true);
				UE_LOG(LogTemp, Warning, TEXT("Important Target: %s"), *TargetBlocks[RandomIndex] -> GetName());
				TargetBlocks.RemoveAt(RandomIndex);
				if(TargetBlocks.Num() == 0)
				{
					break;
				}
			}
		}
	}
}

