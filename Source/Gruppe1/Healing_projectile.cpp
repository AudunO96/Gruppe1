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

	CollisionComp->InitSphereRadius(CollisionRadius);
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComp->SetupAttachment(RootComponent);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// set up overlap
	// CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealing_base::OnOverlapBegin);

	if(!CollisionComp)
		UE_LOG(LogTemp, Warning, TEXT("Collision component missing"))

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	if(!ProjectileMovement)
		UE_LOG(LogTemp, Warning, TEXT("Projectile movement is missing"))

	// sets default life span of projectile to 3 seconds
	InitialLifeSpan = .5f;
}

void AHealing_projectile::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay projectile"))

	UParticleSystemComponent* particleRef = UGameplayStatics::SpawnEmitterAttached(
		projectileParticle,
		RootComponent,
		FName("Trail"),
		FVector(0.f, 0.f, 0.f),
		FRotator(0.f, 0.f, 0.f),
		EAttachLocation::KeepRelativeOffset,
		true
	);

	if (!particleRef)
		UE_LOG(LogTemp, Warning, TEXT("Particle not spawned"))
}