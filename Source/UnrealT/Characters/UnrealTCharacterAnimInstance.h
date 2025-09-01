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

public:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkForward;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkRight;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float HorizontalAngle;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float VerticalAngle;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	AUnrealTCharacter* Character;
};
