// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IAMGameplayInterface.h"

#include "GameFramework/Actor.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

};
