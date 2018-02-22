// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_projectile.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"



// Called every frame
void AHealing_projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation;

	newLocation.X = speed * DeltaTime;

	lengthTraveled += newLocation.X;

	SetActorLocation(GetActorLocation() + newLocation);

	//when at end of trajectory, run deconstructor
	if (lengthTraveled >= travelLength)
		delete this;
}

// sets the travel length and orientation for the projectile
void AHealing_projectile::setTrajectory(FVector trajectory)
{
	trajectory.Y += groundOffset;

	SetActorRotation(trajectory.Rotation());

	travelLength = trajectory.Size();
}