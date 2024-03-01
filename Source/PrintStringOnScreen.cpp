

#include "PrintStringOnScreen.h"

#include "Engine/Engine.h"

void UPrintStringOnScreen::PrintStringOnScreen(FString Message, float Duration, FLinearColor Color, float Size, int Id, bool& bOutSuccess, FString& OutMessage)
{
    GEngine->AddOnScreenDebugMessage(Id, Duration, Color.ToFColor(true), *Message, true, FVector2D(Size));

    bOutSuccess = true;
    OutMessage = FString::Printf(TEXT("Add on success."));
}