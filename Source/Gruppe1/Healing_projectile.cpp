// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_projectile.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBehaviour/PlayerCharacter.h"


AHealing_projectile::AHealing_projectile()
{
	UE_LOG(LogTemp, Warning, TEXT("projectile constructor"))

	if(!CollisionComp)
		UE_LOG(LogTemp, Warning, TEXT("Something wrong, yo"))

	UParticleSystemComponent* particleRef = UGameplayStatics::SpawnEmitterAttached(
		projectileParticle,
		RootComponent,
		FName("Trail"),
		FVector(0.f,0.f,0.f),
		FRotator(0.f, 0.f, 0.f),
		EAttachLocation::KeepRelativeOffset,
		false
	);

	if(!particleRef)
		UE_LOG(LogTemp, Warning, TEXT("Particle not spawned"))

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	//sets default life span of projectile to 3 seconds
	InitialLifeSpan = 3.0f;
}