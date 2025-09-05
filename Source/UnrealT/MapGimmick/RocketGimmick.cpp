// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketGimmick.h"
#include "TimerManager.h"

// Sets default values
ARocketGimmick::ARocketGimmick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARocketGimmick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARocketGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocketGimmick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (APawn* PlayerPawn = Cast<APawn>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(GravityTimerHandle, this, &ARocketGimmick::MoveRocket, 1, false);
	}
}

void ARocketGimmick::MoveRocket()
{
}

