// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMDashProjectile.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>

AIAMDashProjectile::AIAMDashProjectile()
{
	// Custom collision profile
	SphereComp->SetCollisionProfileName("Projectile");
}

void AIAMDashProjectile::Explode_Implementation()
{
	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, OnHitVFX, GetActorLocation(), GetActorRotation());

		EffectComp->DeactivateSystem();

		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		// Rather than destroy, instead start timer
		GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AIAMDashProjectile::Teleport, 0.2f);
	}
}

void AIAMDashProjectile::Teleport()
{
	AActor* Inst = GetInstigator();
	Inst->TeleportTo(GetActorLocation(), Inst->GetActorRotation());
}

void AIAMDashProjectile::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &AIAMDashProjectile::Explode, 0.2f);
}
