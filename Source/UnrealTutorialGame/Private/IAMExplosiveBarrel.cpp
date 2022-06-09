// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMExplosiveBarrel.h"
#include <Components/StaticMeshComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>

// Sets default values
AIAMExplosiveBarrel::AIAMExplosiveBarrel()
{
	// Assign mesh itself in BP because it's an asset
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->ForceStrength = 2500.f;
	ForceComp->Radius = 750.f;
	// ForceComp->DestructibleDamage = 500.f;
	ForceComp->bImpulseVelChange = true;

	MeshComp->SetSimulatePhysics(true);
}

void AIAMExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	MeshComp->OnComponentHit.AddDynamic(this, &AIAMExplosiveBarrel::OnHit);
}

void AIAMExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}

