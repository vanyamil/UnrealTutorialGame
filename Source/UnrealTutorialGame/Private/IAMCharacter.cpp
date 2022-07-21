// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMCharacter.h"

#include "IAMInteractionComponent.h"
#include "IAMAttributeComponent.h"

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <DrawDebugHelpers.h>

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

	InteractionComp = CreateDefaultSubobject<UIAMInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UIAMAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void AIAMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AIAMCharacter::OnHealthChanged);
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

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void AIAMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AIAMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIAMCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AIAMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AIAMCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AIAMCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AIAMCharacter::Dash);
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

void AIAMCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AIAMCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void AIAMCharacter::PrimaryAttack_TimeElapsed()
{
	SendProjectile(PrimaryProjectileClass);
}

void AIAMCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &AIAMCharacter::SecondaryAttack_TimeElapsed, 0.2f);
}

void AIAMCharacter::SecondaryAttack_TimeElapsed()
{
	SendProjectile(SecondaryProjectileClass);
}

void AIAMCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &AIAMCharacter::Dash_TimeElapsed, 0.2f);
}

void AIAMCharacter::Dash_TimeElapsed()
{
	SendProjectile(DashProjectileClass);
}

void AIAMCharacter::PrimaryInteract()
{
	// Since instanced by C++, pretty safe not to pointer guard
	InteractionComp->PrimaryInteract();
}

void AIAMCharacter::OnHealthChanged(AActor* InstigatorActor, UIAMAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void AIAMCharacter::SendProjectile(const TSubclassOf<AActor>& ProjectileClass)
{
	if (ensure(ProjectileClass))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		// Line trace to expected hit location
		AActor* MyOwner = GetOwner();
		FVector EyeLocation = CameraComp->GetComponentLocation();
		FVector EyeEnd = EyeLocation + CameraComp->GetForwardVector() * 4000.f; // randomly picked distance

		FHitResult Hit;
		bool foundHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EyeEnd, { FCollisionObjectQueryParams::InitType::AllObjects });

		// Find direction to point to aim there
		FVector AimAt = foundHit ? Hit.ImpactPoint : EyeEnd;
		FRotator AimAtRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, AimAt);

		FTransform SpawnTM(AimAtRotation, HandLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}
