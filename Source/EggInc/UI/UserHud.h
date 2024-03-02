#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "UserHud.generated.h"

UCLASS()
class UUserHud : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    void InitializeArray();
    void NewFunction();
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

    UPROPERTY(meta=(BindWidget))
    class UButton* HatcheryButton;

	UPROPERTY(EditDefaultsOnly, Category="Chicken")
	TSubclassOf<class ATestChicken> MyTestChicken;

public:
    UFUNCTION()
    void SetAnchor(UCanvasPanel* CanvasPanelAsset, UButton* Button);

    UFUNCTION()
    void OnHatcheryButtonClicked();

    UFUNCTION()
    void OnHatcheryButtonReleased();
    

    void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
       
    bool bIsPressed;

	int32 RandomIndex;

    FVector Location;
	FActorSpawnParameters SpawnInfo;
	FVector Locations[32];


};