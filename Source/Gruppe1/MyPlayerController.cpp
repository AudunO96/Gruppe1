// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "CharacterBehaviour/PlayerCharacter.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "KismetMathLibrary.generated.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}