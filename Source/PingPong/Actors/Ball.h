// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS(Abstract)
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Movement")
	float MovementSpeed = 100.f;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Movement")
	FVector MovementDirection = { 1.0f, 0.f, 0.f };

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* StaticMesh;
	
public:	
	ABall();

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps (TArray< FLifetimeProperty >& OutLifetimeProps) const;

protected:
	virtual void BeginPlay() override;

	virtual void MoveOnTick(float DeltaTime);

	virtual void ReflectDirection(FVector Normal);

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
