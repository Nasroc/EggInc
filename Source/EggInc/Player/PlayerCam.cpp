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

	MovementSpeed = 4.0f;

	bInRange = true;
	


}

// Called every frame
void APlayerCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TouchSetup();

	bInRange = GetLocation();


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



			if(XAbs > 2.0f && YAbs > 2.0f)	
			{
				InitialTouch = CurrentTouch;


				Delta *= MovementSpeed;
				
				Movement = Delta.Size();

				if(bInRange == true){
					SetActorLocation(GetActorLocation() + FVector(Delta.X, Delta.Y, 0.0f));
				}else{
					SetActorLocation(GetActorLocation() + FVector(Delta.X/2, Delta.Y/2, 0.0f));
				}
				
			}else{
				if (XAbs > YAbs) 
				{
					InitialTouch = CurrentTouch;
					if (Delta.X > 0)
					{

						SwipeDirection =  Swipe::Direction::Right;

						Delta.X *= MovementSpeed;

						Movement = Delta.X;

						if(bInRange == true){
							SetActorLocation(GetActorLocation() + FVector(Delta.X, 0.0f, 0.0f));
						}else{
							SetActorLocation(GetActorLocation() + FVector(Delta.X/2, 0.0f, 0.0f));
						}
					}
					else
					{

						SwipeDirection =  Swipe::Direction::Left;

						Delta.X *= MovementSpeed;

						Movement = Delta.X;

						if(bInRange == true){
							SetActorLocation(GetActorLocation() + FVector(Delta.X, 0.0f, 0.0f));
						}else{
							SetActorLocation(GetActorLocation() + FVector(Delta.X/2, 0.0f, 0.0f));
						}
					}
				}
				else
				{
					InitialTouch = CurrentTouch;
					if (Delta.Y > 0)
					{

						SwipeDirection =  Swipe::Direction::Up;

						Delta.Y *= MovementSpeed;

						Movement = Delta.Y;

						if(bInRange == true){
							SetActorLocation(GetActorLocation() + FVector(0.0f, Delta.Y, 0.0f));
						}else{
							SetActorLocation(GetActorLocation() + FVector(0.0f, Delta.Y/2, 0.0f));
						}
					}
					else
					{

						SwipeDirection =  Swipe::Direction::Down;

						Delta.Y *= MovementSpeed;

						Movement = Delta.Y;

						if(bInRange == true){
							SetActorLocation(GetActorLocation() + FVector(0.0f, Delta.Y, 0.0f));
						}else{
							SetActorLocation(GetActorLocation() + FVector(0.0f, Delta.Y/2, 0.0f));
						}
						
					}
				}
			}

		}
	}else if(bIsReleased && bInRange == false){

		switch(SwipeDirection)
		{
			case Swipe::Direction::Up:
				bIsReleased = false;
				break;
			case Swipe::Direction::Down:
				bIsReleased = false;
				break;
			case Swipe::Direction::Left:
				bIsReleased = false;
				break;
			case Swipe::Direction::Right:
				bIsReleased = false;
				break;
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
	bIsReleased = true;

}

bool APlayerCam::GetLocation()
{
	FVector ActorLocation;
	FVector2D Location;

	const FVector2D Origin = FVector2D(0.0f, 0.0f);

	ActorLocation = GetActorLocation();
	Location = FVector2D(ActorLocation.X, ActorLocation.Y);

	float Distance = (Location - Origin).Size();

	Distance += Movement;

	if(Distance < 10000.0f)
	{
		return true;

		
	}else
	{
		return false;

	}

}