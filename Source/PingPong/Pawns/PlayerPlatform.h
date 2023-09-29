// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPlatform.generated.h"

UCLASS(Abstract)
class PINGPONG_API APlayerPlatform : public APawn
{
	GENERATED_BODY()


private:
	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Movement");
	float MovementSpeed = 20;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true));
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* CameraBoom;

public:
	APlayerPlatform();

	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(Server, Reliable, WIthValidation)
	void ServerMoveAlongCameraAxisY(float Value);
	virtual bool ServerMoveAlongCameraAxisY_Validate(float Value);
	virtual void ServerMoveAlongCameraAxisY_Implementation(float Value);
protected:
	virtual void BeginPlay() override;



};
