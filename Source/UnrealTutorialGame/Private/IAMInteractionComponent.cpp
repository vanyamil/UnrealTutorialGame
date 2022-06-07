// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMInteractionComponent.h"
#include "IAMGameplayInterface.h"
#include <DrawDebugHelpers.h>

// Sets default values for this component's properties
UIAMInteractionComponent::UIAMInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIAMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIAMInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UIAMInteractionComponent::PrimaryInteract()
{
	// Do a line trace to find anything we might hit
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	const float SphereRadius = 30.f;

	// FHitResult Hit;
	// bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	FCollisionShape Shape;
	Shape.SetSphere(SphereRadius);
	TArray<FHitResult> Hits;
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// If we do
	for (const FHitResult& Hit : Hits)
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, SphereRadius, 32, LineColor, false, 2.f);

		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UIAMGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IIAMGameplayInterface::Execute_Interact(HitActor, MyPawn);
			break;
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
}

