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

public:	
	
	//Reads the total value and deletes the door if the total value >= value needed
	UFUNCTION(BlueprintCallable, Category = "Corruption Scoring")
		void ReadAndDelete(float corruptionPoints);

	UFUNCTION(BlueprintCallable, Category = "Corruption Scoring")
		void ChangeCorruptionNeeded(float corruptionNeeded);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Corruption Scoring")
		float percentNeeded;

	UPROPERTY(VisibleAnywhere, Category = "Corruption Scoring")
	float corruptionPointsNeeded = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Corruption Scoring")
	float corruptionPointsTotal = 0.0f;
};
