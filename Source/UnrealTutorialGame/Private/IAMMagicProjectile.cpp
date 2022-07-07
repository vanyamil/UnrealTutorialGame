// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMMagicProjectile.h"

#include "IAMAttributeComponent.h"

#include <Components/AudioComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AIAMMagicProjectile::AIAMMagicProjectile()
{
	// Custom collision profile
	SphereComp->SetCollisionProfileName("Projectile");

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
}

void AIAMMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// More consistent to bind here compared to Constructor which may fail to bind if Blueprint was created before adding this binding (or when using hotreload)
	// PostInitializeComponent is the preferred way of binding any events.
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AIAMMagicProjectile::OnActorOverlap);
}

void AIAMMagicProjectile::Explode_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSFX, GetActorLocation());

	Super::Explode_Implementation();
}

void AIAMMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UIAMAttributeComponent* AttributeComp = Cast<UIAMAttributeComponent>(OtherActor->GetComponentByClass(UIAMAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.f);

			Explode();
		}
	}
}

