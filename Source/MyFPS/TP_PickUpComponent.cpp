// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"

#include "Kismet/GameplayStatics.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Set up the Sphere Collision
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AMyFPSCharacter* Character = Cast<AMyFPSCharacter>(OtherActor);
	if(Character != nullptr)
	{
		GEngine->ClearOnScreenDebugMessages();
		// Notify that the actor is being picked up
		UE_LOG(LogTemp, Warning, TEXT("Picked Up!"));
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}