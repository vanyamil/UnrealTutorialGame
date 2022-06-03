// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IAMExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class UNREALTUTORIALGAME_API AIAMExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIAMExplosiveBarrel();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Must be marked with UFUNCTION in order to "bind" the event
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
