// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Enemy_base.h"
#include <vector>
#include "Healing_base.generated.h"

UCLASS()
class GRUPPE1_API AHealing_base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealing_base();

	UFUNCTION(BlueprintCallable)
	void deliverHealing(AEnemy_base* target);

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	std::vector<AEnemy_base> OverlappedActors;
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Collision init")
	float CollisionRadius;

	UPROPERTY(EditAnywhere, Category = "Healing Properties")
	float healStrength;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
