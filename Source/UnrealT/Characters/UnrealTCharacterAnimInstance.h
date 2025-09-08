// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UnrealTCharacterAnimInstance.generated.h"

class AUnrealTCharacter;
/**
 * 
 */
UCLASS()
class UNREALT_API UUnrealTCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkForward;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkRight;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AUnrealTCharacter> Character;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float HorizontalAngle;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float VerticalAngle;
	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float AimingWeightCurrent;
	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float AimingWeightInterpSpeed = 9.f;
	UPROPERTY(BlueprintReadOnly, Category = "Clips")
	float WallDistanceCurrent;
	UPROPERTY(BlueprintReadOnly, Category = "Clips")
	float WallDistanceInterpSpeed = 9.f;

	float WallDistanceLast;
};
