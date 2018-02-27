// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy_base.generated.h"

UCLASS()
class GRUPPE1_API AEnemy_base : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy_base();

	UFUNCTION(BlueprintCallable)
		float recieveHealing(float incomingHealing);

	UFUNCTION(BlueprintCallable)
		float getHealth();

	UFUNCTION(BlueprintCallable)
		float getMaxHealth();

	UFUNCTION(BlueprintCallable)
		void setHealth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(editAnywhere)
	float maxHealth;

	UPROPERTY(VisibleAnywhere)
	float health;

	//Gets called when corruption is 0
	UFUNCTION(BlueprintCallable)
	void RemoveCorruption();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};