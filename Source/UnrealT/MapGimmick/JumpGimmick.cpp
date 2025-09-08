// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpGimmick.h"
#include "UnrealT/Characters/UnrealTCharacter.h"

// Sets default values
AJumpGimmick::AJumpGimmick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJumpGimmick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumpGimmick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AUnrealTCharacter* player = Cast<AUnrealTCharacter>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(GravityTimerHandle, this, &ARocketGimmick::MoveRocket, 1, false);
	}
}

