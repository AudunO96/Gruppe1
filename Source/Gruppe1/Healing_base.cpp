// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_base.h"
#include "CharacterBehaviour/PlayerCharacter.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHealing_base::AHealing_base()
{
	UE_LOG(LogTemp, Warning, TEXT("base constructor"))

	 CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	 // CollisionComp->InitSphereRadius(CollisionRadius);
	 // CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	 // CollisionComp->SetupAttachment(RootComponent);

	 //// Players can't walk on it
	 //CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	 //CollisionComp->CanCharacterStepUpOn = ECB_No;

	 // Set as root component
	 RootComponent = CollisionComp;

	 // set up overlap
	 CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealing_base::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHealing_base::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay base"))
}

// Called every frame
void AHealing_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealing_base::deliverHealing(AEnemyBase* target)
{
	target->recieveHealing(healStrength);

	Destroy();
}

void AHealing_base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *GetName())

	AEnemyBase* target = Cast<AEnemyBase>(OtherActor);

	APlayerCharacter* isPlayer = Cast<APlayerCharacter>(OtherActor);

	
		if (target)
		{
			if(target->getIsCorrupt())
				deliverHealing(target);
		}
		else if (OtherActor != this && !isPlayer)
		{
			Destroy();
		}
}