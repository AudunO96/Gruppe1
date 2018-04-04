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
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
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

	mHealth = mMaxHealth;
	mMana = mMaxMana;
}


void APlayerCharacter::fireProjectile()
{
	// Checks if the projectile exists
	if (ToSpawnProjectile)
	{
		UWorld* world = this->GetWorld();

		//checks if the world exists
		if (world)
		{
			if (UseMana(ProjectileMana))
			{
				// Sets spawn parameters and makes the player character its owner
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;

				// Gets and sets rotation of projectile to be the same as character
				FRotator rotator = this->GetActorRotation();

				// Gets and sets location of projectile to be the same as character + a specified offset
				FVector spawnLocation = this->GetActorLocation() + (this->GetActorForwardVector() * offsetProjectile);

				// Spawns actor at the specified parameters given
				world->SpawnActor<AHealing_projectile>(
					ToSpawnProjectile,
					spawnLocation,
					rotator,
					spawnParams
					);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile is missing"))
	}
}

float APlayerCharacter::GetHealth()
{
	return mHealth;
}

float APlayerCharacter::GetMaxHealth()
{
	return mMaxHealth;
}

void APlayerCharacter::SetHealth(float health)
{
	mHealth += health;

	if (health < 0)
		DamageTaken = true;

	mHealth = FMath::Clamp(mHealth, 0.0f, mMaxHealth);

	HealthPercent = mHealth / mMaxHealth;

	if (mHealth <= 1.0f)
		OnDeath();
}

float APlayerCharacter::GetMana()
{
	return mMana;
}

float APlayerCharacter::GetMaxMana()
{
	return mMaxMana;
}

void APlayerCharacter::SetMana(float mana)
{
	mMana += mana;

	mMana = FMath::Clamp(mMana, 0.0f, mMaxMana);

	ManaPercent = mMana / mMaxMana;
}

bool APlayerCharacter::UseMana(float manaReq)
{
	if (mMana < manaReq)
		return false;
	else
	{
		SetMana(-manaReq);
		return true;
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Checks if the cursor pointer points to something
	if (CursorToWorld != nullptr)
	{
		// Checks if the world exists
		if (UWorld* World = GetWorld())
		{
			// Casts to player controller
			AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
			// Runs a hit result under cursor
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			// Sets the decal on hit surface
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

	if (bShooting)
	{
		//Timer for spawning projectile
		if (GetWorld()->GetTimeSeconds() - mLastShot >= PlayerShotDelay) //change this value to edit the timer for when the character can attack
		{
			fireProjectile();

			mLastShot = GetWorld()->GetTimeSeconds();
		}
	}

	if (mMana != mMaxMana)
		SetMana(ManaRegen * DeltaTime);
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

	InputComponent->BindAction("AttackLine", IE_Pressed, this, &APlayerCharacter::startShoot);
	InputComponent->BindAction("AttackLine", IE_Released, this, &APlayerCharacter::stopShoot);
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

void APlayerCharacter::startShoot()
{
	bShooting = true;
}

void APlayerCharacter::stopShoot()
{
	bShooting = false;
}