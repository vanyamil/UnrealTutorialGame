// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IAMBTTaskNode_RangedAttack.h"

#include "Helpers/PointerHelpers.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Character.h>

EBTNodeResult::Type UIAMBTTaskNode_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EnsuredPtr(AAIController, MyController, OwnerComp.GetAIOwner()) EBTNodeResult::Failed;
	SafePtr(ACharacter, MyPawn, Cast<ACharacter>(MyController->GetPawn())) EBTNodeResult::Failed;

	FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	SafePtr(AActor, TargetActor, Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"))) EBTNodeResult::Failed;

	FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
	FRotator MuzzleRotation = Direction.Rotation();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

	return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
