// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AIAMCharacter::AIAMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AIAMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIAMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIAMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AIAMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIAMCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AIAMCharacter::MoveForward(float AxisValue)
{
	FRotator rot = GetControlRotation();
	rot.Pitch = 0.f;
	rot.Roll = 0.f;

	AddMovementInput(rot.Vector(), AxisValue);
}

void AIAMCharacter::MoveRight(float AxisValue)
{
	// Get forward direction of character
	FRotator rot = GetControlRotation();
	rot.Pitch = 0.f;
	rot.Roll = 0.f;

	// Take Y axis (Right), and rotate it by the ControlRotation - aka find what is 90deg right of character forward
	FVector RightVector = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, AxisValue);
}