// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_base.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHealing_base::AHealing_base()
{
	UE_LOG(LogTemp, Warning, TEXT("base constructor"))

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollisionComp->InitSphereRadius(CollisionRadius);
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComp->SetupAttachment(RootComponent);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// set up overlap
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealing_base::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHealing_base::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("It's-a me, healing"))
}

// Called every frame
void AHealing_base::Tick(float DeltaTime)
{

}

void AHealing_base::deliverHealing(AEnemy_base* target)
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
	UE_LOG(LogTemp, Warning, TEXT("HIT!"))

	AEnemy_base* target = Cast<AEnemy_base>(OtherActor);

	if (target)
	{
		deliverHealing(target);
	}
	else if(OtherActor != this)
	{
		Destroy();
	}
}
	