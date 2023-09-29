// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Components/InputComponent.h"
#include "PingPong/Pawns/PlayerPlatform.h"


void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    if (InputComponent)
    {
        InputComponent->BindAxis
        (FName("MoveRight"),this, &AMainPlayerController::OnMoveRightPressed);
    }
}

void AMainPlayerController::OnMoveRightPressed(float AxisValue)
{
    if (AxisValue == 0) return;
    auto ControlledPawn = Cast<class APlayerPlatform>(GetPawn());
    if (ControlledPawn) {
        ControlledPawn->ServerMoveAlongCameraAxisY(AxisValue);
    }
}
