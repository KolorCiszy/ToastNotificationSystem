// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetPoolingSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Templates/SubclassOf.h"
#include "PoolableWidgetInterface.h"

DEFINE_LOG_CATEGORY(LogWidgetPool);

void UWidgetPoolingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWidgetPoolingSubsystem::Deinitialize()
{
	EmptyAllPools();
	Super::Deinitialize();
}

void UWidgetPoolingSubsystem::ReleaseWidget(UUserWidget* WidgetToRelease)
{
	if (!IsValid(WidgetToRelease)) return;

	if (WidgetToRelease->Implements<UPoolableWidgetInterface>())
	{
		IPoolableWidgetInterface::Execute_OnReleasedToPool(WidgetToRelease);
	}
	WidgetToRelease->RemoveFromParent();
	
	if (auto* PooledWidgetsData = WidgetPool.Find(WidgetToRelease->GetClass()))
	{
		PooledWidgetsData->UsedWidgets.Remove(WidgetToRelease);
	}
	else
	{
		UE_LOG(LogWidgetPool, Error, TEXT("Failed to Find Widget Pool for class: "));
	}
	
}
UUserWidget* UWidgetPoolingSubsystem::GetWidgetFromPool(const TSubclassOf<UUserWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		return nullptr;
	}
	auto AddToUsedWidgets = [&](UUserWidget* WidgetToAdd)
	{
		auto PooledWidgetData = WidgetPool.Find(WidgetClass);
		PooledWidgetData->UsedWidgets.Add(WidgetToAdd);
		
		WidgetToAdd->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
		if (WidgetToAdd->Implements<UPoolableWidgetInterface>())
		{
			IPoolableWidgetInterface::Execute_OnAcquiredFromPool(WidgetToAdd);
		}
		return WidgetToAdd;
	};
	
	UUserWidget* RetrievedWidget{};
	RetrievedWidget = FindFirstUnusedWidgetOfClass(WidgetClass);

	if (!RetrievedWidget)
	{
		RetrievedWidget = AddNewWidgetToPool(WidgetClass);
	}
	if (RetrievedWidget)
	{
		AddToUsedWidgets(RetrievedWidget);
		return RetrievedWidget;
	}
	UE_LOG(LogWidgetPool, Error, TEXT("Failed to get a Widget from Pool"))
	return nullptr;
}
int32 UWidgetPoolingSubsystem::GetUsedWidgetCount(const TSubclassOf<UUserWidget> WidgetClass) const
{
	auto PooledWidgetsData = WidgetPool.Find(WidgetClass);
	if (PooledWidgetsData)
	{
		return PooledWidgetsData->UsedWidgets.Num();
	}
	return INDEX_NONE;
}

TArray<UUserWidget*> UWidgetPoolingSubsystem::GetAllWidgetsInPool(const TSubclassOf<UUserWidget> WidgetClass) const
{
	if (const auto PooledWidgetsData = WidgetPool.Find(WidgetClass))
	{
		return PooledWidgetsData->AllWidgets;
	}
	return TArray<UUserWidget*>();
}


void UWidgetPoolingSubsystem::EmptyPoolOfClass(const TSubclassOf<UUserWidget> WidgetClass)
{
	WidgetPool.FindAndRemoveChecked(WidgetClass);
	UE_LOG(LogWidgetPool, Warning, TEXT("Widget pool of class %s have been emptied."), *WidgetClass->GetName());
}

void UWidgetPoolingSubsystem::EmptyAllPools()
{
	WidgetPool.Empty();
	UE_LOG(LogWidgetPool, Warning, TEXT("All widget pools have been emptied."));
}

UUserWidget* UWidgetPoolingSubsystem::AddNewWidgetToPool(TSubclassOf<UUserWidget> WidgetClass)
{
	if (APlayerController* PC = GetLocalPlayer()->GetPlayerController(GetWorld()))
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(PC, WidgetClass);
		if (NewWidget)
		{
			auto& PooledWidgetsData = WidgetPool.FindOrAdd(WidgetClass);
			PooledWidgetsData.AllWidgets.Add(NewWidget);
			return NewWidget;
		}
	}
	UE_LOG(LogWidgetPool, Error, TEXT("Failed to add new Widget to Pool"));
	return nullptr;
}
UUserWidget* UWidgetPoolingSubsystem::FindFirstUnusedWidgetOfClass(TSubclassOf<UUserWidget> WidgetClass) const
{
	if (!WidgetClass) return nullptr;
		
	const auto PooledWidgetsData = WidgetPool.Find(WidgetClass);
	if (!PooledWidgetsData)
	{
		return nullptr;
	}
	for (auto Widget : PooledWidgetsData->AllWidgets)
	{
		if (!PooledWidgetsData->UsedWidgets.Contains(Widget))
		{
			return Widget;
		}
	}
	return nullptr;
}
