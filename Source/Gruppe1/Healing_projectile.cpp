// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_projectile.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "CharacterBehaviour/PlayerCharacter.h"


AHealing_projectile::AHealing_projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	//sets default life span of projectile to 3 seconds
	InitialLifeSpan = 3.0f;
}

	/*void AHealing_projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT!"))

		AHealing_base* testIfSelf = Cast<AHealing_base>(OtherActor);

	if (!testIfSelf)
	{
		AEnemy_base* target = Cast<AEnemy_base>(OtherActor);

		if (target)
		{
			deliverHealing(target);
		}
		else
		{
			Destroy();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hitting itself"), *this->GetName())
	}
}*/