// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "PlayerCam.h"
#include "Camera/CameraComponent.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Tick")));

}

// Called to bind functionality to input
void APlayerCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCam::TouchInput);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCam::TouchInput);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &APlayerCam::TouchInput);



}

void APlayerCam::TouchInput(ETouchIndex::Type FingerIndex, FVector Location)
{
	
	if (FingerIndex == ETouchIndex::Touch1)
	{
		if (ETouchIndex::Touch1 == IE_Pressed){
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Touch1 Pressed")));
		}else if (ETouchIndex::Touch1 == IE_Repeat){
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Touch1 Repeat")));
		}else{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Touch1 Released")));
		}
	}

}
