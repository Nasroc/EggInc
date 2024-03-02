// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "TestChicken.h"

// Sets default values
ATestChicken::ATestChicken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if(CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	HenHouseLocations[0] = FVector(-1702.0f, 3096.0f, 57.0f);
	HenHouseLocations[1] = FVector(-3041.5f, 1756.0f, 57.0f);
	HenHouseLocations[2] = FVector(-325.5f, 4472.0f, 57.0f);
	HenHouseLocations[3] = FVector(-4373.0f, 422.0f, 57.0f);

}

// Called when the game starts or when spawned
void ATestChicken::BeginPlay()
{
	Super::BeginPlay();

	

	Location = GetHenHouseLocation();
	
}

// Called every frame
void ATestChicken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATestChicken::GetHenHouseLocation()
{
	RandomIndex = FMath::RandRange(0, 3);
	return HenHouseLocations[RandomIndex];
}

