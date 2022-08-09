// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IAMAICharacter.h"

#include "Helpers/PointerHelpers.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <DrawDebugHelpers.h>
#include <Perception/PawnSensingComponent.h>

AIAMAICharacter::AIAMAICharacter()
{
    SenseComp = CreateDefaultSubobject<UPawnSensingComponent>("SenseComp");
}

void AIAMAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    SenseComp->OnSeePawn.AddDynamic(this, &AIAMAICharacter::OnPawnSeen);
}

void AIAMAICharacter::OnPawnSeen(APawn* Pawn)
{
	SafePtr(AAIController, MyController, Cast<AAIController>(GetController()));
	SafePtr(UBlackboardComponent, Blackboard, MyController->GetBlackboardComponent());
    Blackboard->SetValueAsObject("TargetActor", Pawn);

    DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}
