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


protected:

	//Here we set the percent of healing needed for the door to disappear
	UPROPERTY(EditAnywhere, Category = "Corruption Scoring")
		float mPercentNeeded;

	//Total points of corruption needed for the door to disappear
	UPROPERTY(VisibleAnywhere, Category = "Corruption Scoring")
	float mCorruptionPointsNeeded = 0.0f;

	//Here we add the total corruption points together, which is then compared to corruptionPointsNeeded
	UPROPERTY(VisibleAnywhere, Category = "Corruption Scoring")
	float mCorruptionPointsTotal = 0.0f;
};
