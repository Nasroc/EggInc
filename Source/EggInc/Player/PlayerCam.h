// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCam.generated.h"


UENUM(BlueprintType)
 namespace Swipe{
	enum Direction {
	 Up,
	 Down,
	 Left,
	 Right
 };

 }
UCLASS()
class EGGINC_API APlayerCam : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCam();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchSetup();

	bool GetLocation();

	FVector2D InitialTouch;
	FVector2D CurrentTouch;

	Swipe::Direction SwipeDirection;

	bool bIsPressed;
	bool bIsReleased;
	bool bInRange;

	float Movement;
	float MovementSpeed;
	float SlowSpeed;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ButtonPressed();


private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* CameraComponent;
	
		
	
	



};
