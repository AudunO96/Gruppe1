// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_projectile.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


AHealing_projectile::AHealing_projectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ABulletRefProjectile::OnHit);		// set up a notification for when this component hits something blocking

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
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called every frame
void AHealing_projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealing_projectile::BeginPlay()
{
	FVector velocity;
	velocity.X = speed;
	GetRootComponent()->ComponentVelocity = velocity;
}

// sets the travel length and orientation for the projectile
void AHealing_projectile::setTrajectory(FVector trajectory)
{
	trajectory.Y += groundOffset;

	SetActorRotation(trajectory.Rotation());

	travelLength = trajectory.Size();
}