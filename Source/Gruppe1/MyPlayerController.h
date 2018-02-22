// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GRUPPE1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AMyPlayerController();

protected:

	//PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
};
