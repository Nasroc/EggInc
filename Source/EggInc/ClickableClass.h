// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "ClickableClass.generated.h"

UCLASS()
class EGGINC_API AClickableClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClickableClass();

	// The box component that will be used for clicking/touching
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clickable")
	UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the actor is clicked/touched
	UFUNCTION()
	void OnInputTouchBegin(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	// Called when the actor stops being clicked/touched
	UFUNCTION()
	void OnInputTouchEnd(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Clickable")
	void OpenMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clickable")
	bool bShouldOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clickable")
	FString MenuName = "Menu";
};
