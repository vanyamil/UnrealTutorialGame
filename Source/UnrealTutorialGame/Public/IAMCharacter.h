// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "IAMCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UIAMInteractionComponent;
class UIAMAttributeComponent;
class UAnimMontage;

UCLASS()
class UNREALTUTORIALGAME_API AIAMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIAMCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UIAMInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UIAMAttributeComponent* AttributeComp;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
	FTimerHandle TimerHandle_Dash;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack();
	void SecondaryAttack_TimeElapsed();
	void Dash();
	void Dash_TimeElapsed();
	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UIAMAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

private:
	void SendProjectile(const TSubclassOf<AActor>& ProjectileClass);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
