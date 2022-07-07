// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMAttributeComponent.h"

#include <Math/UnrealMathUtility.h>

// Sets default values for this component's properties
UIAMAttributeComponent::UIAMAttributeComponent()
{
	HealthMax = 100.f;
	Health = HealthMax;
}

bool UIAMAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool UIAMAttributeComponent::ApplyHealthChange(float Delta)
{
	float NewHealth = FMath::Clamp(Health + Delta, 0.f, HealthMax);
	Delta = NewHealth - Health;
	Health = NewHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

