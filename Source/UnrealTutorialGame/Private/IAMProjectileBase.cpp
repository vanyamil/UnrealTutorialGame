// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMProjectileBase.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>

DEFINE_LOG_CATEGORY(LogProjectile);

// Sets default values
AIAMProjectileBase::AIAMProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->InitSphereRadius(20.f);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ActiveEffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;
}

void AIAMProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	// More consistent to bind here compared to Constructor which may fail to bind if Blueprint was created before adding this binding (or when using hotreload)
	// PostInitializeComponent is the preferred way of binding any events.
	SphereComp->OnComponentHit.AddDynamic(this, &AIAMProjectileBase::OnActorHit);
}

void AIAMProjectileBase::PostInitProperties()
{
	Super::PostInitProperties();

	MovementComp->InitialSpeed = InitialSpeed;
}

void AIAMProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogProjectile, Log, TEXT("[AIAMProjectileBase::OnActorHit] Start"));
	if (!OtherActor || OtherActor != GetInstigator()) 
	{
		UE_LOG(LogProjectile, Log, TEXT("[AIAMProjectileBase::OnActorHit] Explode because actor isn't instigator"));
		Explode();
	}
}

// _Implementation from it being marked as BlueprintNativeEvent
void AIAMProjectileBase::Explode_Implementation()
{
	UE_LOG(LogProjectile, Log, TEXT("[AIAMProjectileBase::Explode_Implementation] Start"));
	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, OnHitVFX, GetActorLocation(), GetActorRotation());

		EffectComp->DeactivateSystem();

		MovementComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		Destroy();
	}
}
