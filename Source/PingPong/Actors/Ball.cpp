// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Net/UnrealNetwork.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	SetTickableWhenPaused(false);
	SetActorTickEnabled(false);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);

	SetReplicateMovement(true);
	bReplicates = true;

}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority()) {
		MoveOnTick(DeltaTime);
	}

}

void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABall, MovementSpeed);
	DOREPLIFETIME(ABall, MovementDirection);
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::MoveOnTick(float DeltaTime)
{
	auto WorldOffset = MovementDirection * (MovementSpeed * DeltaTime);
	AddActorWorldOffset(WorldOffset, true);
}

void ABall::ReflectDirection(FVector Normal)
{
	if (HasAuthority()) {
		auto NewNormal = Normal;
		NewNormal.Z = 0;
		auto NewDirection = FMath::GetReflectionVector(MovementDirection, NewNormal);
		MovementDirection = NewDirection;
	}
}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority()) {
		ReflectDirection(Hit.Normal);
		MoveOnTick(0.01);
	}
}



