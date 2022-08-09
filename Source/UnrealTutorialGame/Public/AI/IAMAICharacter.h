// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IAMAICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class UNREALTUTORIALGAME_API AIAMAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AIAMAICharacter();

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* SenseComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
};
