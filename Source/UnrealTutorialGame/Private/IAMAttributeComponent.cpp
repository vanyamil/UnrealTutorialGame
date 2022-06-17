// Fill out your copyright notice in the Description page of Project Settings.


#include "IAMAttributeComponent.h"

// Sets default values for this component's properties
UIAMAttributeComponent::UIAMAttributeComponent()
{
	Health = 100.f;
}


bool UIAMAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

