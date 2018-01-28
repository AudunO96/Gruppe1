// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Gruppe1.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::MoveX(float Value)
{
	// finner retningen karakteren står i
	FRotator Rotation = Controller->GetControlRotation();

	// legger til bevegelse i retningen
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveY(float Value)
{
	// finner retningen karakteren står i
	FRotator Rotation = Controller->GetControlRotation();

	// legger til bevegelse i retningen
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::Interact()
{

}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
	isJumping = bPressedJump;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
	isJumping = bPressedJump;
}