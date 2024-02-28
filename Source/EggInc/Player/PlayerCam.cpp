// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "PlayerCam.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"

// Sets default values
APlayerCam::APlayerCam()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	// Create a camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComponent->SetOrthoWidth(10000.0f);
	CameraComponent->bConstrainAspectRatio = true;
	CameraComponent->AspectRatio = 0.5625f;


	RootComponent = CameraComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APlayerCam::BeginPlay()
{
	Super::BeginPlay();

	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch = -25.0f;
	NewRotation.Yaw = 90.0f;
	SetActorRotation(NewRotation);
	SetActorLocation(FVector(0.0f, 0.0f, 3000.0f));
	


}

// Called every frame
void APlayerCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TouchSetup();
}

// Called to bind functionality to input
void APlayerCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCam::BeginTouch);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCam::EndTouch);

}

void APlayerCam::TouchSetup()
{

	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("TouchSetup"));

	if (bIsPressed)
	{
		FVector2D TempLocation;
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

		if(PlayerController)
		{
			bool bIsCurrentlyPressed;
			PlayerController->GetInputTouchState(ETouchIndex::Touch1, TempLocation.X, TempLocation.Y, bIsCurrentlyPressed);
		}

		float Length = (InitialTouch - TempLocation).Size();

		if (Length > 0.0f)
		{
			CurrentTouch = TempLocation;

			FVector2D Delta = CurrentTouch - InitialTouch;
			float XAbs = FMath::Abs(Delta.X);
			float YAbs = FMath::Abs(Delta.Y);


			/*
				Fix the issue where player can only move on the x-axis or y-axis at a time
			*/




			if (XAbs > YAbs) 
			{
				InitialTouch = CurrentTouch;
				if (Delta.X > 0)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Right"));

					Delta.X *= 2.0f;

					SetActorLocation(GetActorLocation() + FVector(Delta.X, 0.0f, 0.0f));
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left"));

					Delta.X *= 2.0f;

					SetActorLocation(GetActorLocation() + FVector(Delta.X, 0.0f, 0.0f));
				}
			}
			else
			{
				InitialTouch = CurrentTouch;
				if (Delta.Y > 0)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Up"));

					Delta.Y *= 2.0f;

					SetActorLocation(GetActorLocation() + FVector(0.0f, Delta.Y, 0.0f));
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Down"));

					Delta.Y *= 2.0f;

					SetActorLocation(GetActorLocation() + FVector(0.0f, Delta.Y, 0.0f));
				}
			}

		}
	}
}

void APlayerCam::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsPressed = true;
	FVector2D TempLocation;
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	if(PlayerController)
	{
		bool bIsCurrentlyPressed;
		PlayerController->GetInputTouchState(ETouchIndex::Touch1, TempLocation.X, TempLocation.Y, bIsCurrentlyPressed);
	}

	InitialTouch = TempLocation;
}


void APlayerCam::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsPressed = false;
	IF_COND = true;
}