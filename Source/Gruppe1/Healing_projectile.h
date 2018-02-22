// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healing_base.h"
#include "Healing_projectile.generated.h"


/**
 * 
 */
UCLASS()
class GRUPPE1_API AHealing_projectile : public AHealing_base
{
	GENERATED_BODY()
	
public:
	void setTrajectory(FVector trajectory);


protected:
	float travelLength;
	float lengthTraveled{0};

	UPROPERTY(EditAnywhere)
	float speed;

	UPROPERTY(EditAnywhere)
	float groundOffset;


public:

	virtual void Tick(float DeltaTime) override;
};
