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
    //Add locations behind the start location
    Locations[0] = FVector(-1500.0f, -610.0f, 80.0f);
    Locations[1] = FVector(-1700.0f, -610.0f, 80.0f);
    Locations[2] = FVector(-1900.0f, -610.0f, 80.0f);
    Locations[3] = FVector(-2000.0f, -610.0f, 80.0f);

    //Add locations in front of the start location
    Locations[4] = FVector(-1300.0f, -610.0f, 80.0f);
    Locations[5] = FVector(-1100.0f, -610.0f, 80.0f);
    Locations[6] = FVector(-900.0f, -610.0f, 80.0f);
    Locations[7] = FVector(-700.0f, -610.0f, 80.0f);

    //Add locations to the left of the start location
    Locations[8] = FVector(-1500.0f, -810.0f, 80.0f);
    Locations[9] = FVector(-1500.0f, -1010.0f, 80.0f);
    Locations[10] = FVector(-1500.0f, -1210.0f, 80.0f);
    Locations[11] = FVector(-1500.0f, -1410.0f, 80.0f);

    //Add locations to the right of the start location
    Locations[12] = FVector(-1500.0f, -410.0f, 80.0f);
    Locations[13] = FVector(-1500.0f, -210.0f, 80.0f);
    Locations[14] = FVector(-1500.0f, -10.0f, 80.0f);
    Locations[15] = FVector(-1500.0f, 190.0f, 80.0f);

    //Add locations to the front right of the start location
    Locations[16] = Locations[0];
    Locations[17] = Locations[0];
    Locations[18] = Locations[0];
    Locations[19] = Locations[0];

    //Add locations to the front left of the start location
    Locations[20] = FVector(-1700.0f, -410.0f, 80.0f);
    Locations[21] = FVector(-1900.0f, -210.0f, 80.0f);
    Locations[22] = FVector(-2100.0f, -10.0f, 80.0f);
    Locations[23] = FVector(-2200.0f, 90.0f, -20.0f);

    //Add locations to the back right of the start location
    Locations[24] = FVector(-1500.0f, -810.0f, 80.0f);
    Locations[25] = FVector(-1700.0f, -1010.0f, 80.0f);
    Locations[26] = FVector(-1900.0f, -810.0f, 80.0f);
    Locations[27] = FVector(-2000.0f, -1010.0f, 80.0f);

    //Add locations to the back left of the start location
    Locations[28] = FVector(-1700.0f, -810.0f, 80.0f);
    Locations[29] = FVector(-1900.0f, -1010.0f, 80.0f);
    Locations[30] = Locations[0];
    Locations[31] = Locations[1];


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
        RandomIndex = FMath::RandRange(0, 31);
        Location = Locations[RandomIndex];
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
        GetWorld()->SpawnActor<ATestChicken>(MyTestChicken, Location, Rotation, SpawnInfo);
        
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Button Released"));
    }
}