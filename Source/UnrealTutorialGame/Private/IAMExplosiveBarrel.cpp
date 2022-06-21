// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMExplosiveBarrel.h"

#include "IAMAttributeComponent.h"

#include <Components/StaticMeshComponent.h>
#include <DrawDebugHelpers.h>
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

	// If an actor with health touches it, give it damage
	if(OtherActor)
	{
		UIAMAttributeComponent* Attr = Cast<UIAMAttributeComponent>(OtherActor->GetComponentByClass(UIAMAttributeComponent::StaticClass()));
		if (Attr)
		{
			Attr->ApplyHealthChange(-50.f);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorHir in Explosive Barrel"));

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %.2f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.f, true);
}

