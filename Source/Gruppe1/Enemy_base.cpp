// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_base.h"
#include "Healing_base.h"
#include "Healing_projectile.h"


// Sets default values
AEnemy_base::AEnemy_base()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AEnemy_base::recieveHealing(float incomingHealing)
{
	health -= incomingHealing;

	health = FMath::Clamp(health, 0.0f, maxHealth);

	if (health == 0.0f)
		RemoveCorruption();

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
	
}

void AEnemy_base::RemoveCorruption()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is now healed"), *this->GetName())
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