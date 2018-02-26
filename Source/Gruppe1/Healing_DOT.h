// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healing_base.h"
#include "Healing_DOT.generated.h"


/*
 * 
 */

UCLASS()
class GRUPPE1_API AHealing_DOT : public AHealing_base
{
	GENERATED_BODY()

public:
	AHealing_DOT();
	
		/** Sphere collision component */
		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UBoxComponent* CollisionComp;

public:	

		virtual void Tick(float DeltaTime) override;
	
};
