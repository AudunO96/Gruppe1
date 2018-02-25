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

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
	
public:
	AHealing_projectile();
	void setTrajectory(FVector trajectory);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float travelLength{ 1 };
	float lengthTraveled{ 0 };

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float groundOffset;


public:

	virtual void Tick(float DeltaTime) override;
};
