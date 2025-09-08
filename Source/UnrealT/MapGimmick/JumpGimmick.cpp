// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpGimmick.h"
#include "UnrealT/Characters/UnrealTCharacter.h"

// Sets default values
AJumpGimmick::AJumpGimmick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;

	MeshComp->SetGenerateOverlapEvents(true);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	MeshComp->OnComponentHit.AddDynamic(this, &AJumpGimmick::OnHit);
	MeshComp->OnComponentEndOverlap.AddDynamic(this, &AJumpGimmick::OnEndOverlap);
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
		if (prevPower == FVector::ZeroVector)
			prevPower = player->GetOriginLaunchPower();

		FVector overridePower = player->GetOriginLaunchPower() * ModifyJumpPower;
		player->SetLaunchPower(overridePower);
	}
}

void AJumpGimmick::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AUnrealTCharacter* player = Cast<AUnrealTCharacter>(OtherActor))
	{
		player->SetLaunchPower(prevPower);
	}
}

