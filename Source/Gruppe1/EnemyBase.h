// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "CorruptionDoor.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class GRUPPE1_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

	float recieveHealing(float incomingHealing);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void updateHealthbar();

	UFUNCTION(BlueprintImplementableEvent, Category = "Healing")
		void onRemoveCorruption();

	/*UFUNCTION(BlueprintImplementableEvent, Category = "Healing")
	void removeCorruptionBP();
	*/
	UFUNCTION(BlueprintCallable)
		float getHealth();

	UFUNCTION(BlueprintCallable)
		float getMaxHealth();

	UFUNCTION(BlueprintCallable)
		void setHealth();

	FORCEINLINE bool getIsCorrupt() { return isCorrupt; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(editAnywhere)
		float maxHealth;

	UPROPERTY(VisibleAnywhere)
		float health;

	//Gets called when corruption is 0
	UFUNCTION(BlueprintCallable, Category = "Healing")
		void removeCorruption();

	UPROPERTY(EditAnywhere, Category = "Door")
	ACorruptionDoor* Doorptr = nullptr;

	UPROPERTY()
		bool isCorrupt = true;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
