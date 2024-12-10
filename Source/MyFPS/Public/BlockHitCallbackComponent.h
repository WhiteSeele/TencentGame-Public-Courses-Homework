// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockHitCallbackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPS_API UBlockHitCallbackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlockHitCallbackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetIsImportantTarget(bool bIsImportant);
	void SetTargetMaterial(UMaterialInterface* Material);
	void ApplyTargetMaterial();

private:
	bool bIsHitOnce;
	bool bIsImportantTarget;

	UPROPERTY(EditAnywhere, Category = "Hit Score Configuration")
	int32 Score = 10;

	UPROPERTY(EditAnywhere, Category = "Hit Scale Configuration")
	float Scale = 0.3;

	UPROPERTY(EditAnywhere, Category = "Target Material")
	UMaterialInterface* TargetMaterial;
};
