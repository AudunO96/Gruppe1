// Fill out your copyright notice in the Description page of Project Settings.

#include "HealingCircle.h"


AHealingCircle::AHealingCircle()
{
	CollisionComp->InitSphereRadius(CollisionRadius);
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComp->SetupAttachment(RootComponent);

	// Set as root component
	RootComponent = CollisionComp;

	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AHealingCircle::OnOverlapEnd);
}

void AHealingCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (AEnemy_base* enemy : OverlappedActors)
	{
		enemy->recieveHealing(healStrength * DeltaTime);
	}
}

void AHealingCircle::deliverHealing(AEnemy_base* target)
{
	for (AEnemy_base* enemy : OverlappedActors)
	{
		if (enemy == target)
		{
			return;
		}
	}
	OverlappedActors.push_back(target);
}

void AHealingCircle::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	int pos{ 0 };

	for (AEnemy_base* enemy : OverlappedActors)
	{
		if (enemy == OtherActor)
		{
			OverlappedActors.erase(OverlappedActors.begin()+pos);

			return;
		}
		else
		{
			pos++;
		}
	}
}