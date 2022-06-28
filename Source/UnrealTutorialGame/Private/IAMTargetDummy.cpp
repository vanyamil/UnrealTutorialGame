// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMTargetDummy.h"

#include "IAMAttributeComponent.h"

#include <Components/StaticMeshComponent.h>

// Sets default values
AIAMTargetDummy::AIAMTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UIAMAttributeComponent>("AttributeComp");

	AttributeComp->OnHealthChanged.AddDynamic(this, &AIAMTargetDummy::OnHealthChanged);
}

void AIAMTargetDummy::OnHealthChanged(AActor* InstigatorActor, UIAMAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

