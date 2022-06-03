// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMExplosiveBarrel.h"
#include <Components/StaticMeshComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>

// Sets default values
AIAMExplosiveBarrel::AIAMExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Assign mesh itself in BP because it's an asset
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->ForceStrength = 2000.f;
	ForceComp->Radius = 400.f;

	MeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AIAMExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIAMExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

