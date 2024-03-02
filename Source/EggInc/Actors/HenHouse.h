#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HenHouse.generated.h"

UCLASS()
class EGGINC_API AHenHouse : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AHenHouse();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};