// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "CorruptionDoor.h"
#include "EnemyMeleeAttack.h"
#include "GameFramework/Character.h"
#include "CharacterBehaviour/PlayerCharacter.h"
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

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void DamagePlayer();

	UFUNCTION(BlueprintImplementableEvent, Category = "Healing")
	void onRemoveCorruption();

	UFUNCTION(BlueprintCallable, Category ="Health")
	float getHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float getMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void setHealth();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void meleeAttack();

	// Overlap
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
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

	UPROPERTY(EditAnywhere, Category = "Damage")
	float mDamage;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<class AEnemyMeleeAttack> ToSpawnMelee;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float offsetMelee;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float attackDelay;

	bool bCanAttack;
	float attackStart;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
