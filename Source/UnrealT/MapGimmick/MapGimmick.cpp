// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

// Sets default values
AMapGimmick::AMapGimmick()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetEnableGravity(false);
	MeshComp->SetGenerateOverlapEvents(true);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	MeshComp->OnComponentHit.AddDynamic(this, &AMapGimmick::OnHit);
}

// Called when the game starts or when spawned
void AMapGimmick::BeginPlay()
{
	Super::BeginPlay();

}

void AMapGimmick::EnableGravity()
{
	MeshComp->SetEnableGravity(true);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                // Ű (-1�̸� �Ź� �� �޽���)
			2.0f,              // ȭ�鿡 ǥ�õ� �ð� (��)
			FColor::Green,     // ���� ��
			TEXT("Hello Debug!") // ǥ���� ���ڿ�
		);
	}
}

void AMapGimmick::OnHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("�浹 �߻�!"));
	}

	if (APawn* PlayerPawn = Cast<APawn>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(GravityTimerHandle, this, &AMapGimmick::EnableGravity, DelayBeforeGravity, false);
	}
}

// Called every frame
void AMapGimmick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

