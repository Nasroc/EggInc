// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class EGGINC_API UMyButton : public UButton
{
	GENERATED_BODY()


public:
	UMyButton();

	void PressButton();

	UPROPERTY()
	class UMyUserWidget* MyUserWidget;


	
};
