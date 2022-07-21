// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IAMBTService_CheckAttackRange.h"

#include "Helpers/PointerHelpers.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Actor.h>
#include <GameFramework/Pawn.h>

void UIAMBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between AI Pawn and TargetActor

	EnsuredPtr(UBlackboardComponent, Blackboard, OwnerComp.GetBlackboardComponent());
	SafePtr(AActor, TargetActor, Cast<AActor>(Blackboard->GetValueAsObject("TargetActor")));
	EnsuredPtr(AAIController, MyController, OwnerComp.GetAIOwner());
	EnsuredPtr(APawn, MyPawn, MyController->GetPawn());

	const float Dist = FVector::Distance(TargetActor->GetActorLocation(), MyPawn->GetActorLocation());
	const bool bWithinRange = Dist < 2000.f;

	const bool bHasLOS = bWithinRange && MyController->LineOfSightTo(TargetActor);

	Blackboard->SetValueAsBool(AttackRangeKey.SelectedKeyName, bHasLOS);
}