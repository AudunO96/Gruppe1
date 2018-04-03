// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Healing_projectile.h"
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

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void fireProjectile();

	/*UFUNCTION(BlueprintCallable, Category = "Spawn")
	void coneSpell();*/

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AHealing_projectile> ToSpawnProjectile;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class AHealing_DOT> ToSpawnCone;*/

	UPROPERTY(EditAnywhere, Category = "Spawn")
		float offsetProjectile;

	/*UPROPERTY(EditAnywhere, Category = "Spawn")
		float offsetCone;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns CursorToWorld subobject
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jumping")
	bool isJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	bool canJumpHigh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	bool canGlide;

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

	UPROPERTY(EditAnywhere)
	float TimerCount;

	UFUNCTION(BlueprintCallable, Category = "Death")
	void OnDeath();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	void SetHealth(float health);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float HealthPercent = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	float GetMana();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	float GetMaxMana();

	UFUNCTION(BlueprintCallable, Category = "Player Stats")
	void SetMana(float mana);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float ManaPercent = 1.0f;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	TArray<bool> Upgrades;
	*/

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Character)
	class UCapsuleComponent* CollisionComp;

private: 

	bool UseMana(float manaReq);
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	bool bCone = false;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float mMaxHealth;

	float mHealth;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float mMaxMana;

	float mMana;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float ProjectileMana;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float ManaRegen;

	void startShoot();
	void stopShoot();

	bool bShooting;
};
