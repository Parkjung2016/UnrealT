// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealTCharacterAnimInstance.h"
#include "UnrealTCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UUnrealTCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AUnrealTCharacter>(TryGetPawnOwner());
}

void UUnrealTCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)
		return;

	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0.f;

	FRotator ActorRot = Character->GetActorRotation();
	FVector Forward = UKismetMathLibrary::GetForwardVector(ActorRot);
	FVector Right = UKismetMathLibrary::GetRightVector(ActorRot);

	WalkForward = FVector::DotProduct(Forward, Velocity);
	WalkRight = FVector::DotProduct(Right, Velocity);

	IsFalling = Character->GetCharacterMovement()->IsFalling();
	APlayerController* PC = Cast<APlayerController>(Character->GetController());
	if (PC)
	{
		FRotator ControlRot = PC->GetControlRotation();
		FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, ActorRot);

		HorizontalAngle = DeltaRot.Yaw;
		VerticalAngle = DeltaRot.Pitch;
	}

	WallDistanceLast = Character->GetWallDistance();
	UE_LOG(LogTemp, Warning, TEXT("WallDistanceLast: %f"), WallDistanceLast);
	WallDistanceCurrent = UKismetMathLibrary::FInterpTo(WallDistanceCurrent, WallDistanceLast, DeltaSeconds,
	                                                    WallDistanceInterpSpeed);
}
