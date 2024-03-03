#include "UserHud.h"
#include "G:\UEGames\EggInc\Source\EggInc\Player\PlayerCam.h"
#include "G:\UEGames\EggInc\Source\EggInc\Actors\TestChicken.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"


#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet2/BlueprintEditorUtils.h"
#endif
/**
 * Fills the text blocks in the user HUD.
 * This function is responsible for populating the text blocks in the user HUD with the appropriate data.
 * It retrieves the canvas panel from the widget blueprint generated class and clears its children.
 * Then, it creates a button widget using ConstructWidget and adds it as a child to the canvas panel.
 * Finally, it marks the blueprint as structurally modified to ensure the changes are saved.
 */


void UUserHud::FillTextBlocks()
{
#if WITH_EDITOR
	if (!CanvasPanel)
		return;

	UWidgetBlueprintGeneratedClass* WidgetBlueprintGeneratedClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());

	UPackage* Package = WidgetBlueprintGeneratedClass->GetPackage();
	UWidgetBlueprint* MainAsset = Cast<UWidgetBlueprint>(Package->FindAssetInPackage());

	// We *cannot* use the BindWidget-marked GridPanel, instead we need to get the widget in the asset's widget tree.
	// However thanks to the BindWidget, we can be relatively sure that FindWidget will be successful.
	UCanvasPanel* AssetCanvasPanel = Cast<UCanvasPanel>(MainAsset->WidgetTree->FindWidget("CanvasPanel"));

    AssetCanvasPanel->SetToolTipText(FText::FromString("This is a tooltip"));

	AssetCanvasPanel->ClearChildren();

        const FString WidgetName = FString::Printf(TEXT("HatcheryButton"));
        // Create widget with ConstructWidget, not NewObject
        HatcheryButton = MainAsset->WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), FName(*WidgetName));

        AssetCanvasPanel->AddChildToCanvas(HatcheryButton);
        SetAnchor(AssetCanvasPanel, HatcheryButton);

	AssetCanvasPanel->Modify();

	MainAsset->Modify();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(MainAsset);
#endif
}

void UUserHud::NativeConstruct()
{
    Super::NativeConstruct();

    InitializeArray();

    bIsPressed = false;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UserHud Constructed"));
    HatcheryButton->OnPressed.AddDynamic(this, &UUserHud::OnHatcheryButtonClicked);
    HatcheryButton->OnReleased.AddDynamic(this, &UUserHud::OnHatcheryButtonReleased);
    Location = FVector(0.0f, 0.0f, 0.0f);
}

void UUserHud::InitializeArray()
{

    Locations[0] = FVector(-1374.332805, -1094.670723f, 180.006230f);
    Locations[1] = FVector(-1526.891787f, -942.111741f, 180.006232f);
    Locations[2] = FVector(-1667.444592f, -801.558936f, 180.006233f);
    Locations[3] = FVector(-1817.471699f, -651.531829f, 180.006233f);
    Locations[4] = FVector(-1947.245803f, -521.757725f, 180.006234f);


}

void UUserHud::SetAnchor(UCanvasPanel* CanvasPanelAsset, UButton* Button)
{
    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Button->Slot);
    CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
    CanvasSlot->SetSize(FVector2D(1200.0f, 300.0f));
    CanvasSlot->SetPosition(FVector2D(0.0f, 1400.0f));
}


void UUserHud::OnHatcheryButtonClicked()
{
    
    bIsPressed = true;
    
    

}

void UUserHud::OnHatcheryButtonReleased()
{
    bIsPressed = false;
}

void UUserHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bIsPressed)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Button Pressed"));
        const FRotator Rotation(0.0f, 0.0f, 0.0f);
        RandomIndex = FMath::RandRange(0, 4);
        Location = Locations[RandomIndex];
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
        GetWorld()->SpawnActor<ATestChicken>(MyTestChicken, Location, Rotation, SpawnInfo);
        
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Button Released"));
    }
}