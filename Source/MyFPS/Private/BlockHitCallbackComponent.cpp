// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFPS/Public/BlockHitCallbackComponent.h"

#include "MyFPS/MyFPSCharacter.h"
#include "MyFPS/MyFPSProjectile.h"


// Sets default values for this component's properties
UBlockHitCallbackComponent::UBlockHitCallbackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bIsHitOnce = false;
	bIsImportantTarget = false;
	TargetMaterial = nullptr;
}


// Called when the game starts
void UBlockHitCallbackComponent::BeginPlay()
{
	Super::BeginPlay();
	// Register the OnHit function to the OnComponentHit event of the parent actor's mesh component
	if(AActor* Owner = GetOwner())
	{
		if(UStaticMeshComponent* MeshComp = Owner->FindComponentByClass<UStaticMeshComponent>())
		{
			MeshComp->OnComponentHit.AddDynamic(this, &UBlockHitCallbackComponent::OnHit);
		}
	}
}


// Called every frame
void UBlockHitCallbackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBlockHitCallbackComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyFPSProjectile* Projectile = Cast<AMyFPSProjectile>(OtherActor);
	AMyFPSCharacter* Player = Cast<AMyFPSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Projectile)
	{
		const int32 Points = bIsImportantTarget ? Score * 2 : Score;
		if(!bIsHitOnce)
		{
			bIsHitOnce = true;
			if(Player)
			{
				if(bIsImportantTarget)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Important Target Hit!"));
					UE_LOG(LogTemp, Warning, TEXT("Important Target Hit!"));
				}
				Player->AddScore(Points);
			}
			GetOwner() -> SetActorScale3D(GetOwner() -> GetActorScale3D() * Scale);
		}
		else
		{
			if(bIsImportantTarget)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Important Target Hit!"));
				UE_LOG(LogTemp, Warning, TEXT("Important Target Hit!"));
			}
			Player->AddScore(Points);
			GetOwner() -> Destroy();
		}
		Projectile->Destroy();
	}
}

void UBlockHitCallbackComponent::SetIsImportantTarget(bool bIsImportant)
{
	bIsImportantTarget = bIsImportant;
	if(bIsImportantTarget)
	{
		ApplyTargetMaterial();
	}
}

void UBlockHitCallbackComponent::ApplyTargetMaterial()
{
	if(TargetMaterial)
	{
		if(AActor* Owner = GetOwner())
		{
			if(UStaticMeshComponent* MeshComp = Owner->FindComponentByClass<UStaticMeshComponent>())
			{
				UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(TargetMaterial, this);
				MeshComp->SetMaterial(0, DynamicMaterial);
			}
		}
	}
}

void UBlockHitCallbackComponent::SetTargetMaterial(UMaterialInterface* Material)
{
	TargetMaterial = Material;
}