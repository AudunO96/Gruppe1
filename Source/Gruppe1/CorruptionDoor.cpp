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
// Handles corruption points and deletion of the door
void ACorruptionDoor::ReadAndDelete(float corruptionPoints)
{
	// Increments corruptionPoints with corruptionPointsTotal
	mCorruptionPointsTotal += mCorruptionPoints;

	//Checks to see if the specific amount of points needed has been met and destroys the door if it is true
	if (corruptionPointsNeeded != 0)
	{
		if (mCorruptionPointsTotal / mCorruptionPointsNeeded >= mPercentNeeded)
		{
			UE_LOG(LogTemp, Warning, TEXT("DELET THIS"))

				Destroy();
		}
	}
		
}
/* 
Increments corruptionNeeded with corruptionPointsNeeded

This is updated for how many enemies are pointed at the door, and is then converted to a per cent number 
(range from 0.0-1.0 is set in the door to see how much percent it needs)
*/
void ACorruptionDoor::ChangeCorruptionNeeded(float corruptionNeeded)
{
	mCorruptionPointsNeeded += corruptionNeeded;
}

// Called every frame
void ACorruptionDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

