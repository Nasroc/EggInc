#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PrintStringOnScreen.generated.h"


UCLASS()

class UPrintStringOnScreen : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Print String On Screen")
    static void PrintStringOnScreen(FString Message, float Duration, FLinearColor Color, float Size, int Id, bool& bOutSuccess, FString& OutMessage);



}; 