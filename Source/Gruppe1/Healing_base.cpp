// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_base.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHealing_base::AHealing_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealing_base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealing_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AHealing_base::deliverHealing(float deltaTime)
{
	return healStrength * deltaTime;
}