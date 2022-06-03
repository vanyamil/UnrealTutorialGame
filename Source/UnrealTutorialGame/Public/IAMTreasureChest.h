// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IAMGameplayInterface.h"
#include "IAMTreasureChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREALTUTORIALGAME_API AIAMTreasureChest : public AActor, public IIAMGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIAMTreasureChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
