// Created by Carson Benedetto on 02-26-2024 GitHub Copyright (c) 2024 Nasroc Productions All Rights Reserved


#include "MyUserWidget.h"



void UMyUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(WidgetTree)
    {
        UPanelWidget* RootWidget = WidgetTree->ConstructWidget<UPanelWidget>(UPanelWidget::StaticClass(), TEXT("RootWidget"));
        WidgetTree->RootWidget = RootWidget;
    }

    UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

    Chickens = WidgetTree->ConstructWidget<UMyButton>(UMyButton::StaticClass(), TEXT("Chickens"));
    
}


void UMyUserWidget::AddToScreen()
{
    AddToViewport();
}

void UMyUserWidget::ReleaseChickens()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ReleaseChickens()"));
}

void UMyUserWidget::OnButtonClicked()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnButtonClicked()"));
}
