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

	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void DamagePlayer();

	UFUNCTION(BlueprintImplementableEvent, Category = "Healing")
	void onRemoveCorruption();

	UFUNCTION(BlueprintCallable, Category ="Health")
	float getHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float getMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void setHealth();

	FORCEINLINE bool getIsCorrupt() { return mIsCorrupt; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Gets called when corruption is 0
	UFUNCTION(BlueprintCallable, Category = "Healing")
	void removeCorruption();

	UPROPERTY(editAnywhere)
	float mMaxHealth;

	UPROPERTY(VisibleAnywhere)
	float mHealth;

	UPROPERTY()
	bool mIsCorrupt = true;

	UPROPERTY(EditAnywhere, Category = "Door")
	ACorruptionDoor* Doorptr = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
