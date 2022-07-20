// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IAMAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class UNREALTUTORIALGAME_API AIAMAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;
};
