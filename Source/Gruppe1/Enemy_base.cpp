// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_base.h"
#include "Healing_base.h"
#include "GameFramework/Actor.h"
#include "algorithm"
#include "Healing_projectile.h"


// Sets default values
AEnemy_base::AEnemy_base()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AEnemy_base::recieveHealing(float incomingHealing)
{
	incomingHealing = std::min(incomingHealing, health);

	health -= incomingHealing;

	this->updateHealthbar();

	if(Doorptr)
		Doorptr->ReadAndDelete(incomingHealing);
	else
		UE_LOG(LogTemp, Error, TEXT("Missing door pointer for: %s"), *this->GetName())

	health = FMath::Clamp(health, 0.0f, maxHealth);

	if (health == 0.0f)
		removeCorruption();

	UE_LOG(LogTemp, Error, TEXT("TRUE OR FALSE: %s"), (bGenerateOverlapEventsDuringLevelStreaming ? TEXT("True") : TEXT("False")))

	return health;
}

float AEnemy_base::getHealth()
{
	return health;
}

float AEnemy_base::getMaxHealth()
{
	return maxHealth;
}

void AEnemy_base::setHealth()
{
	health = maxHealth;
}

// Called when the game starts or when spawned
void AEnemy_base::BeginPlay()
{
	Super::BeginPlay();

	if (Doorptr)
		Doorptr->ChangeCorruptionNeeded(maxHealth);
}

//void AEnemy_base::RemoveCorruption()
//{
//	UE_LOG(LogTemp, Warning, TEXT("%s is now healed"), *this->GetName())
//
//	removeCorruptionBP();
//}

void AEnemy_base::removeCorruption()
{
	isCorrupt = false;
}

// Called every frame
void AEnemy_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy_base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}