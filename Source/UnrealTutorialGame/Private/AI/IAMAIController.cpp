// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IAMAIController.h"

#include "Helpers/PointerHelpers.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

void AIAMAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}
