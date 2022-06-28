// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IAMTargetDummy.generated.h"

class UIAMAttributeComponent;

UCLASS()
class UNREALTUTORIALGAME_API AIAMTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIAMTargetDummy();

protected:
	
	UPROPERTY(VisibleAnywhere)
	UIAMAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UIAMAttributeComponent* OwningComp, float NewHealth, float Delta);
};
