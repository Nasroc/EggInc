// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "TestChicken.generated.h"

UCLASS()
class EGGINC_API ATestChicken : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestChicken();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Chicken")
	FVector GetHenHouseLocation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FVector HenHouseLocations[4];

	int32 RandomIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chicken")
	FVector Location;

	
};
