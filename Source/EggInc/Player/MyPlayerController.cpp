// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
    bShowMouseCursor = true;
    bEnableTouchEvents = true;
    bEnableTouchOverEvents = true;
    EnableInput(this);

    
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    PlayerCam = Cast<APlayerCam>(GetPawn());

}
