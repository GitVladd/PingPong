// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPlatform.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerPlatform::APlayerPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetIsReplicated(true);

	SetRootComponent(StaticMesh);


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(StaticMesh);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; 
	CameraBoom->SetIsReplicated(true);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; 
	CameraComponent->SetIsReplicated(true);

	

}

void APlayerPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerPlatform, MovementSpeed);
}

void APlayerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

bool APlayerPlatform::ServerMoveAlongCameraAxisY_Validate(float Value) {
	if (Value > 1.f || Value < -1.f)return false;  
	return true;
}


void APlayerPlatform::ServerMoveAlongCameraAxisY_Implementation(float Value)
{
	if (CameraComponent != nullptr && Value != 0.f) {
		const FRotator YawRotation(0.f, CameraComponent->GetComponentRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		auto WorldOffset = Direction * MovementSpeed * Value;
		AddActorWorldOffset(WorldOffset, true);
	}
}

void APlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


