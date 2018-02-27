// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorruptionDoor.generated.h"

UCLASS()
class GRUPPE1_API ACorruptionDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACorruptionDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Corruption Scoring")
		void ReadAndDelete(float corruptionPoints);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Corruption Scoring")
		float corruptionPointsNeeded;

	UPROPERTY(EditAnywhere, Category = "Corruption Scoring")
		float corruptionPointsTotal;
};
