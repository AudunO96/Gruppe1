// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GRUPPE1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveX(float Value);

	UFUNCTION()
		void MoveY(float Value);

	UFUNCTION()
		void Interact();

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jumping")
	bool isJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
		bool canJumpHigh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
		bool canGlide;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	TArray<bool> PassengerSeats;
	*/
};
