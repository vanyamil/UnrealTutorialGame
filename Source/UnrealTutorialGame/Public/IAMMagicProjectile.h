// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IAMProjectileBase.h"

#include "GameFramework/Actor.h"

#include "IAMMagicProjectile.generated.h"

UCLASS()
class UNREALTUTORIALGAME_API AIAMMagicProjectile : public AIAMProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIAMMagicProjectile();

protected:

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
