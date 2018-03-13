// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
<<<<<<< HEAD
#include "Components/SphereComponent.h"
#include "Enemy_base.h"
=======
>>>>>>> parent of 64fea4e... Broke everything
#include "Healing_base.generated.h"

UCLASS()
class GRUPPE1_API AHealing_base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealing_base();

	UFUNCTION(BlueprintCallable)
<<<<<<< HEAD
	virtual void deliverHealing(AEnemy_base* target);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
=======
	float deliverHealing(float deltaTime = 1.0f);
>>>>>>> parent of 64fea4e... Broke everything

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

<<<<<<< HEAD
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Collision init")
	float CollisionRadius;
=======
	
>>>>>>> parent of 64fea4e... Broke everything

	UPROPERTY(EditAnywhere, Category = "Healing Properties")
	float healStrength;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
