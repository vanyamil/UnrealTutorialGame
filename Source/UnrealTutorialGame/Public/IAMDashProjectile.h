// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IAMProjectileBase.h"
#include "IAMDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTUTORIALGAME_API AIAMDashProjectile : public AIAMProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIAMDashProjectile();

protected:
	FTimerHandle TimerHandle_Explode;
	FTimerHandle TimerHandle_Teleport;

	void Teleport();
	void Explode_Implementation() override;
	void BeginPlay() override;
};
