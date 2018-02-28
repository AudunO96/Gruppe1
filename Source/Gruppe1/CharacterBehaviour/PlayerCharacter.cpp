// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Gruppe1.h"
#include "Materials/Material.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"
#include "Healing_DOT.h"
#include "Math/Vector.h"
#include "Engine.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set as root component
	RootComponent = CollisionComp;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Blueprints/HUD/Decal.Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void APlayerCharacter::fireProjectile()
{
	if (ToSpawnProjectile)
	{
		UWorld* world = this->GetWorld();

		if (world)
		{
			FActorSpawnParameters spawnParams;
			//spawnParams.Owner = this;

			FRotator rotator = this->GetActorRotation();

			FVector spawnLocation = this->GetActorLocation() + (this->GetActorForwardVector() * offsetProjectile);

			AHealing_projectile* projectileRef = world->SpawnActor<AHealing_projectile>(ToSpawnProjectile, spawnLocation, rotator, spawnParams);

			//projectileRef->setTrajectory(projectileTrajectory);
		}
	}
}

void APlayerCharacter::coneSpell()
{
	bCone = true;
	if (ToSpawnCone)
	{
		UWorld* World = this->GetWorld();

		if (bCone)
		{
			if (World)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				FRotator rotator = this->GetActorRotation();
				FVector spawnLocation = this->GetActorLocation() + (this->GetActorForwardVector() * offsetCone);

				World->SpawnActor<AHealing_DOT>(ToSpawnCone, spawnLocation, rotator, spawnParams);
				/*
					FString stringRef = CollisionComp->GetName();
					FName nameRef = FName(*stringRef);
					Cast<AHealing_DOT>(ToSpawnCone)->AttachTo(this, nameRef, EAttachLocation::SnapToTarget, false);
				*/
				//projectileRef->setTrajectory(projectileTrajectory);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nothing is pointed at here"));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr)
	{
		if (UWorld* World = GetWorld())
		{
			AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			projectileTrajectory = CursorFV;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
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

	InputComponent->BindAction("AttackLine", IE_Pressed, this, &APlayerCharacter::fireProjectile);

	InputComponent->BindAction("AttackCone", IE_Pressed, this, &APlayerCharacter::coneSpell);
	InputComponent->BindAction("AttackLine", IE_Released, this, &APlayerCharacter::stopConeSpell);

}

void APlayerCharacter::MoveX(float Value)
{
	// finner retningen karakteren staar i
	FRotator Rotation = Controller->GetControlRotation();

	// legger til bevegelse i retningen
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveY(float Value)
{
	// finner retningen karakteren staar i
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
	isJumping = !isJumping;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
	isJumping = !isJumping;
}

void APlayerCharacter::stopConeSpell()
{
	bCone = false;
}

void APlayerCharacter::OnDeath()
{
}

