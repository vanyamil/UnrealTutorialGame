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

	InitialSpeed = 5000.f;
}

void AIAMDashProjectile::Explode_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[AIAMDashProjectile::Explode_Implementation] Start"));
	// Since this can be called by parts of code from base class, remove timer that could trigger it a second time.
	GetWorldTimerManager().ClearTimer(TimerHandle_Explode);

	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, OnHitVFX, GetActorLocation(), GetActorRotation());

		EffectComp->DeactivateSystem();

		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		// Rather than destroy, instead start timer
		FTimerHandle TimerHandle_Teleport;
		GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AIAMDashProjectile::Teleport, 0.2f);
	}
}

void AIAMDashProjectile::Teleport()
{
	UE_LOG(LogTemp, Log, TEXT("Starting teleport"));
	AActor* Inst = GetInstigator();
	if (ensure(Inst))
	{
		Inst->TeleportTo(GetActorLocation(), Inst->GetActorRotation());
	}

	if (!Destroy())
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to destroy"));
	}
}

void AIAMDashProjectile::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &AIAMDashProjectile::Explode, 0.2f);
}
