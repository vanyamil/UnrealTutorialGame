// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMTreasureChest.h"

// Sets default values
AIAMTreasureChest::AIAMTreasureChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;

}

// Called when the game starts or when spawned
void AIAMTreasureChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIAMTreasureChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIAMTreasureChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

