

#include "Depot.h"

// Sets default values
ADepot::ADepot()
{
 	// Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);
   

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

    if(CubeVisualAsset.Succeeded())
    {
        VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
    

}

// Called when the game starts or when spawned
void ADepot::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ADepot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

