// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healing_base.h"
#include <vector>
#include "HealingCircle.generated.h"

/**
 * 
 */
UCLASS()
class GRUPPE1_API AHealingCircle : public AHealing_base
{
	GENERATED_BODY()
	
public:
	AHealingCircle();

	void deliverHealing(AEnemy_base* target) override;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
	
private:
	std::vector<AEnemy_base*> OverlappedActors;

public: 
	virtual void Tick(float DeltaTime) override;
};
