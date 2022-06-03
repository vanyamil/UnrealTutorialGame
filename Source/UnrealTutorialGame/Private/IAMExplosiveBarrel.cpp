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
	ForceComp->ForceStrength = 200000.f;
	ForceComp->Radius = 4000.f;
	ForceComp->DestructibleDamage = 500.f;

	MeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AIAMExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentHit.AddDynamic(this, &AIAMExplosiveBarrel::OnHit);
}

void AIAMExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}

