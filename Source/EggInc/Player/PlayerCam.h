// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCam.generated.h"

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

	void TouchInput(const ETouchIndex::Type FingerIndex, const FVector Location);




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* CameraComponent;
	
		
	
	



};
