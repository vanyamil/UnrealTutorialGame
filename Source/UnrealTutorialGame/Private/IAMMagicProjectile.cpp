// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMMagicProjectile.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AIAMMagicProjectile::AIAMMagicProjectile()
{
	// Custom collision profile
	SphereComp->SetCollisionProfileName("Projectile");
}

