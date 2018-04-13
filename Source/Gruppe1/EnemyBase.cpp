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
	
	//Collider for melee attack detection range
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderBox"));
	SphereComponent->InitSphereRadius(150.0f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::BeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnOverlapEnd);
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

void AEnemyBase::meleeAttack()
{
	// Checks if the projectile exists
	if (ToSpawnMelee)
	{
		UWorld* world = this->GetWorld();

		//checks if the world exists
		if (world)
		{
			// Sets spawn parameters and makes the player character its owner
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			// Gets and sets rotation of projectile to be the same as character
			FRotator rotator = this->GetActorRotation();

			// Gets and sets location of projectile to be the same as character + a specified offset
			FVector spawnLocation = this->GetActorLocation() + (this->GetActorForwardVector() * offsetMelee);

			// Spawns actor at the specified parameters given
			world->SpawnActor<AHealing_projectile>(
				ToSpawnMelee,
				spawnLocation,
				rotator,
				spawnParams
				);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack is missing"))
	}
}

void AEnemyBase::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(Cast<APlayerCharacter>(OtherActor))
	bCanAttack = true;
}

void AEnemyBase::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerCharacter>(OtherActor))
	bCanAttack = false;
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
	//Checks if the enemy can attack
	if (bCanAttack)
	{
		//Checks if it's too early to attack, attacks if it's not
		if (GetWorld()->GetTimeSeconds() - attackStart >= attackDelay)
		{
			meleeAttack();
		}
	}

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}