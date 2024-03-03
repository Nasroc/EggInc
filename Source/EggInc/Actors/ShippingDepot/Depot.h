#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Depot.generated.h"

UCLASS()
class EGGINC_API ADepot : public AActor
{
    GENERATED_BODY()

public:

    ADepot();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;



protected:

    virtual void BeginPlay() override;


public:

    virtual void Tick(float DeltaTime) override;




};