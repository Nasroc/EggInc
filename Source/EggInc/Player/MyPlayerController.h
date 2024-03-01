// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "G:\UEGames\EggInc\Source\EggInc\UI\MyUserWidget.h"
#include "Engine/InputTouchDelegateBinding.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCam.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.generated.h"



/**
 * 
 */
UCLASS()
class EGGINC_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMyPlayerController();
	virtual void BeginPlay() override;

	UPROPERTY()
	class UMyUserWidget* UserInterface;

	UPROPERTY()
	class UMyUserWidget* MyUserWidget;

	

protected:



protected:
	class APlayerCam* PlayerCam;

	
};
