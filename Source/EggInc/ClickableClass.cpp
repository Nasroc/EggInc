// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "ClickableClass.h"

// Sets default values
AClickableClass::AClickableClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box component to handle the clicking
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	if(BoxComponent)
	{
		BoxComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
		BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
	}

}

// Called when the game starts or when spawned
void AClickableClass::BeginPlay()
{
	Super::BeginPlay();

	// Bind the OnInputTouchBegin function to the OnInputTouchBegin event
	if(BoxComponent)
	{
	BoxComponent->OnInputTouchBegin.AddDynamic(this , &AClickableClass::OnInputTouchBegin);
	BoxComponent->OnInputTouchEnd.AddDynamic(this , &AClickableClass::OnInputTouchEnd);
	}

	
}

// Called every frame
void AClickableClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the actor is clicked/touched
void AClickableClass::OnInputTouchBegin(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	// Destroy the actor when it is clicked
	bShouldOpen = true;
}

// Called when the actor stops being clicked/touched
void AClickableClass::OnInputTouchEnd(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	// Destroy the actor when it is clicked

	TouchedComponent->GetChildComponent(0);
	if(bShouldOpen)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TouchedComponent->GetChildComponent(0)->GetName() + " was clicked");
		bShouldOpen = false;
	}else{
		bShouldOpen = false;
	}
		
}

void AClickableClass::OpenMenu()
{
	// Open the menu

}