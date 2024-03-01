// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyButton.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "MyUserWidget.generated.h"



UCLASS()
class EGGINC_API UMyUserWidget : public UUserWidget
{
GENERATED_BODY()

public:




protected:
	virtual void NativeConstruct() override;
	void OnButtonClicked();
	

public:
	void AddToScreen();

	UPROPERTY(CallInEditor, BlueprintReadWrite, meta = (BindWidget))
	class UMyButton* Chickens;


	UFUNCTION()
	void ReleaseChickens();

	
};
