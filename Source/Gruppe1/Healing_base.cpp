// Fill out your copyright notice in the Description page of Project Settings.

#include "Healing_base.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHealing_base::AHealing_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollisionComp->InitSphereRadius(CollisionRadius);
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComp->SetupAttachment(RootComponent);

	if (!CollisionComp)
		UE_LOG(LogTemp, Error, TEXT("Collision for %s is missing"), *this->GetName())
	else
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealing_base::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHealing_base::BeginPlay()
{

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
	