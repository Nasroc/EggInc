#include "BUIEditorTestWidget.h"

#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Kismet2/BlueprintEditorUtils.h"
#endif

void UBUIEditorTestWidget::FillTextBlocks()
{
#if WITH_EDITOR
	if (!GridPanel)
		return;

	UWidgetBlueprintGeneratedClass* WidgetBlueprintGeneratedClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());

	UPackage* Package = WidgetBlueprintGeneratedClass->GetPackage();
	UWidgetBlueprint* MainAsset = Cast<UWidgetBlueprint>(Package->FindAssetInPackage());

	// We *cannot* use the BindWidget-marked GridPanel, instead we need to get the widget in the asset's widget tree.
	// However thanks to the BindWidget, we can be relatively sure that FindWidget will be successful.
	UGridPanel* AssetGridPanel = Cast<UGridPanel>(MainAsset->WidgetTree->FindWidget("GridPanel"));

	AssetGridPanel->ClearChildren();
	for (int32 Y = 0; Y < Height; ++Y)
	{
		for (int32 X = 0; X < Width; ++X)
		{
			const FString WidgetName = FString::Printf(TEXT("Text_X%d_Y%x"), X, Y);
			// Create widget with ConstructWidget, not NewObject
			UTextBlock* Text = MainAsset->WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName(WidgetName));
			Text->SetText(FText::FromString(WidgetName));

			AssetGridPanel->AddChildToGrid(Text, X, Y);
		}
	}
	AssetGridPanel->Modify();

	MainAsset->Modify();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(MainAsset);
#endif
}