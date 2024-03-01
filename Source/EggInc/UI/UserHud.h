#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserHud.generated.h"

UCLASS()
class UUserHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Marking a parameterless function with CallInEditor makes a button
	// show up in editor with that name (see screenshot)
	UFUNCTION(CallInEditor, Category="Editor Fill Test")
	void FillTextBlocks();

    

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category="Editor Fill Test", meta=(UIMin=1, UIMax=10, ClampMin=1, ClampMax=10))
	int32 Width = 2;
	UPROPERTY(EditAnywhere, Category="Editor Fill Test", meta=(UIMin=1, UIMax=10, ClampMin=1, ClampMax=10))
	int32 Height = 2;
#endif

	// We don't use GridPanel directly in this example, but it being BindWidget means Unreal
	// will display an error if there is no correctly-named variable.
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* CanvasPanel;

public:
    UFUNCTION()
    void SetAnchor(UCanvasPanel* CanvasPanelAsset, UButton* Button, FAnchors Min, FAnchors Max);

};