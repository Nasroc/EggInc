#include "UserHud.h"
#include "G:\UEGames\EggInc\Source\EggInc\Player\PlayerCam.h"
#include "G:\UEGames\EggInc\Source\EggInc\TestChicken.h"
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

    bIsPressed = false;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UserHud Constructed"));
    HatcheryButton->OnPressed.AddDynamic(this, &UUserHud::OnHatcheryButtonClicked);
    HatcheryButton->OnReleased.AddDynamic(this, &UUserHud::OnHatcheryButtonReleased);
    Location = FVector(0.0f, 0.0f, 0.0f);
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
    const FRotator Rotation(0.0f, 0.0f, 0.0f);
    const FActorSpawnParameters SpawnInfo;
    GetWorld()->SpawnActor<ATestChicken>(Location, Rotation, SpawnInfo);
    Location.X += 100.0f;

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
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, TEXT("Button Released"));
    }
}