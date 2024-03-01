// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "MyButton.h"



#include "MyUserWidget.h" // Add the missing include statement

UMyButton::UMyButton()
{
    OnPressed.AddDynamic(this, &UMyButton::PressButton);

    SetVisibility(ESlateVisibility::Visible);
    SetIsEnabled(true);
}

void UMyButton::PressButton()
{
    if (MyUserWidget) // Check if MyUserWidget is valid before calling the function
    {
        MyUserWidget->ReleaseChickens();
    }
}