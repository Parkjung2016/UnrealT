// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UnrealTCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AUnrealTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUnrealTCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Aiming(const FInputActionValue& Value);

	UFUNCTION()
	void UpdateWallDistance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> FireAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> AimingAction;

	UPROPERTY(EditAnywhere)
	float MaxWallCheckDistance = 200.f;
	UPROPERTY(EditAnywhere)
	FVector LaunchPower;

public:
	float GetWallDistance() const { return WallDistance; }
	bool GetIsAiming() const { return IsAiming; }

	void SetLaunchPower(const FVector& launchPower) { OverrideLaunchPower = launchPower; }
	void SetLaunchPower() { OverrideLaunchPower = FVector::ZeroVector; }

private:
	FTimerHandle UpdateWallTimerHandle;
	FVector OverrideLaunchPower;
	float WallDistance;
	bool IsAiming;
	bool IsAimingButtonPressed;
};
