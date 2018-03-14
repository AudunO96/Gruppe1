// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healing_base.h"
#include "ParticleDefinitions.h"
#include "Healing_projectile.generated.h"


/**
 * 
 */
UCLASS()
class GRUPPE1_API AHealing_projectile : public AHealing_base
{
	GENERATED_BODY()
public: 

	AHealing_projectile();
	
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* projectileParticle;

	UFUNCTION()
	virtual void BeginPlay() override;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
