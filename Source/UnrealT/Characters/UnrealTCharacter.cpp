// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealTCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUnrealTCharacter::AUnrealTCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetMesh(), TEXT("head"));
	CameraComponent->SetRelativeLocation(FVector(0.f, 20.0f, 0.f)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 18.0f, 0.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
}

void AUnrealTCharacter::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("UpdateWallDistance"));

	GetWorld()->GetTimerManager().SetTimer(UpdateWallTimerHandle, TimerDelegate, .03f, true);
}

void AUnrealTCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetCharacterMovement()->IsFalling())
	{
		if (IsAiming)
			IsAiming = false;
	}
	else if (IsAiming != IsAimingButtonPressed)
	{
		IsAiming = IsAimingButtonPressed;
	}
}

void AUnrealTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction.Get(), ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction.Get(), ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &AUnrealTCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction.Get(), ETriggerEvent::Triggered, this, &AUnrealTCharacter::Look);
		EnhancedInputComponent->BindAction(FireAction.Get(), ETriggerEvent::Triggered, this, &AUnrealTCharacter::Fire);
		EnhancedInputComponent->BindAction(AimingAction.Get(), ETriggerEvent::Triggered, this,
			&AUnrealTCharacter::Aiming);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
			TEXT(
				"'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
			), *GetNameSafe(this));
	}
}


void AUnrealTCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUnrealTCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUnrealTCharacter::Fire(const FInputActionValue& Value)
{
	FVector launchDirection = -CameraComponent->GetForwardVector();
	if (!IsAiming)
	{
		float randomX = FMath::FRandRange(-1.f, 1.f);
		float randomY = FMath::FRandRange(-1.f, 1.f);
		float randomZ = FMath::FRandRange(-1.f, 1.f);

		FVector randomVector = FVector(randomX, randomY, randomZ);

		launchDirection += randomVector;
		launchDirection.Normalize();
	}
	else
	{
		// FVector Velocity = GetVelocity();
		// float speed = Velocity.Size();
		//
		// float randomSpread = speed * 0.1f;
		//
		// FVector randomVector = FMath::VRand();
		// launchDirection += randomVector * randomSpread;
		// launchDirection.Normalize();
	}
	FVector launchVelocity = launchDirection;
	if (OverrideLaunchPower != FVector::ZeroVector)
	{
		launchVelocity *= OverrideLaunchPower;
	}
	else
		launchVelocity *= LaunchPower;
	LaunchCharacter(launchVelocity, false, true);
}

void AUnrealTCharacter::Aiming(const FInputActionValue& Value)
{
	if (GetCharacterMovement()->IsFalling())return;;
	bool isAiming = Value.Get<bool>();
	IsAimingButtonPressed = isAiming;
	IsAiming = isAiming;
	CameraComponent->FieldOfView = IsAiming ? 80.f : 90.f;
}

void AUnrealTCharacter::UpdateWallDistance()
{
	FVector startPoint = CameraComponent->GetComponentLocation();
	FVector endDirection = CameraComponent->GetForwardVector() * MaxWallCheckDistance;
	FVector endPoint = startPoint + endDirection;
	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	bool result = GetWorld()->LineTraceSingleByChannel(hitResult, startPoint, endPoint, ECC_Camera, params);
	if (result)
	{
		float distance = FVector::Distance(startPoint, hitResult.Location);
		WallDistance = distance / MaxWallCheckDistance;
	}
	else
	{
		WallDistance = 1.0f;
	}
}