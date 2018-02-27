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

float AEnemy_base::recieveHealing(float IncomingHealing)
{
	if (Health < IncomingHealing)
	{
		IncomingHealing = Health;
	}
	Health -= IncomingHealing;

	Doorptr->ReadAndDelete(IncomingHealing);

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if (Health == 0.0f)
		RemoveCorruption();

	return Health;
}

float AEnemy_base::GetHealth()
{
	return Health;
}

float AEnemy_base::GetMaxHealth()
{
	return MaxHealth;
}

void AEnemy_base::SetHealth()
{
	Health = MaxHealth;
}

// Called when the game starts or when spawned
void AEnemy_base::BeginPlay()
{
	Super::BeginPlay();
	
	Doorptr->ChangeCorruptionNeeded(MaxHealth);
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