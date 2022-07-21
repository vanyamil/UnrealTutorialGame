// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IAMAIController.h"

#include "Helpers/PointerHelpers.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

void AIAMAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	// Eventually - pawn sensing
	SafePtr(APawn, MyPawn, UGameplayStatics::GetPlayerPawn(this, 0));

	//GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
}
