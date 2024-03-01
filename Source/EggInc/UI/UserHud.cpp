#include "UserHud.h"

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
        UButton* HatcheryButton = MainAsset->WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), FName(*WidgetName));

        AssetCanvasPanel->AddChildToCanvas(HatcheryButton);
        SetAnchor(AssetCanvasPanel, HatcheryButton, FAnchors(0.5, 0.5), FAnchors(0.5, 0.5));

	AssetCanvasPanel->Modify();

	MainAsset->Modify();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(MainAsset);
#endif
}

void UUserHud::SetAnchor(UCanvasPanel* CanvasPanelAsset, UButton* Button, FAnchors Min, FAnchors Max)
{
    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Button->Slot);
    CanvasSlot->SetAnchors(Min);
}