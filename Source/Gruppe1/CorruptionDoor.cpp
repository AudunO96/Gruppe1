// Fill out your copyright notice in the Description page of Project Settings.

#include "CorruptionDoor.h"


// Sets default values
ACorruptionDoor::ACorruptionDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACorruptionDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACorruptionDoor::ReadAndDelete(float corruptionPoints)
{
	corruptionPointsTotal += corruptionPoints;

	if (corruptionPointsTotal / corruptionPointsNeeded > percentNeeded)
		delete this;
}

void ACorruptionDoor::ChangeCorruptionNeeded(float corruptionNeeded)
{
	percentNeeded += corruptionNeeded;
}

// Called every frame
void ACorruptionDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

