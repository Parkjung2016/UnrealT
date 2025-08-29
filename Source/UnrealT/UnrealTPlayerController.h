// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnrealTPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class UNREALT_API AUnrealTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

protected:

	virtual void BeginPlay() override;

};
