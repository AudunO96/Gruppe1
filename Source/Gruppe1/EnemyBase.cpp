// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Healing_base.h"
#include "GameFramework/Actor.h"
#include "algorithm"
#include "GameFramework/MovementComponent.h"
#include "Healing_projectile.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AEnemyBase::recieveHealing(float incomingHealing)
{
	incomingHealing = std::min(incomingHealing, mHealth);

	mHealth -= incomingHealing;

	this->updateHealthbar();

	if (Doorptr)
		Doorptr->ReadAndDelete(incomingHealing);
	else
		UE_LOG(LogTemp, Error, TEXT("Missing door pointer for: %s"), *this->GetName())

		mHealth = FMath::Clamp(mHealth, 0.0f, mMaxHealth);

	if (mHealth == 0.0f)
		removeCorruption();

	UE_LOG(LogTemp, Error, TEXT("TRUE OR FALSE: %s"), (bGenerateOverlapEventsDuringLevelStreaming ? TEXT("True") : TEXT("False")))

		return mHealth;
}

float AEnemyBase::getHealth()
{
	return mHealth;
}

float AEnemyBase::getMaxHealth()
{
	return mMaxHealth;
}

void AEnemyBase::setHealth()
{
	mHealth = mMaxHealth;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (Doorptr)
		Doorptr->ChangeCorruptionNeeded(mMaxHealth);
}

//void AEnemy_base::RemoveCorruption()
//{
//	UE_LOG(LogTemp, Warning, TEXT("%s is now healed"), *this->GetName())
//
//	removeCorruptionBP();
//}

void AEnemyBase::removeCorruption()
{
	mIsCorrupt = false;

	onRemoveCorruption();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}