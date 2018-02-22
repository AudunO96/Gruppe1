// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_projectile.h"


// Called every frame
void AHealing_projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation;

	newLocation.X = speed * DeltaTime;

	SetActorLocation(GetActorLocation() + newLocation);
}

void AHealing_projectile::setTrajectory(FVector trajectory)
{
	SetActorRotation(trajectory.Rotation());

	travelLength = trajectory.Size();
}