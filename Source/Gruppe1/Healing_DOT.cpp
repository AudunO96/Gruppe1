// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_DOT.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"

AHealing_DOT::AHealing_DOT()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;
}

// Called every frame
void AHealing_DOT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



