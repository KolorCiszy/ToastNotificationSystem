// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WidgetPoolingSubsystem.generated.h"

USTRUCT()
struct FPooledWidgetsData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> AllWidgets;

	UPROPERTY()
	TSet<TObjectPtr<UUserWidget>> UsedWidgets;
};

DECLARE_LOG_CATEGORY_EXTERN(LogWidgetPool, Log, All);

/**
 * 
 */
UCLASS()
class UIPRACTICE_API UWidgetPoolingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;
	
	// Returns a widget to the pool
	UFUNCTION(BlueprintCallable, Category = "UI|Pooling")
	void ReleaseWidget(UUserWidget* WidgetToRelease);

	// Gets widget from pool or created a new one if not found
	UFUNCTION(BlueprintCallable, Category = "UI|Pooling", meta = (DeterminesOutputType = "WidgetClass"))
	UUserWidget* GetWidgetFromPool(const TSubclassOf<UUserWidget> WidgetClass);

	// Returns current instance count of a give widget class
	UFUNCTION(BlueprintCallable, Category = "UI|Pooling")
	int32 GetUsedWidgetCount(const TSubclassOf<UUserWidget> WidgetClass) const;

	UFUNCTION(BlueprintPure, Category = "UI|Pooling")
	TArray<UUserWidget*> GetAllWidgetsInPool(const TSubclassOf<UUserWidget> WidgetClass) const;

	
	template<typename T>
	T* GetWidgetFromPool(const TSubclassOf<UUserWidget> WidgetClass = T::StaticClass())
	{
		return Cast<T>(GetWidgetFromPool(T::StaticClass()));
	}
	
	// Clears the pool of widgets of input class
	UFUNCTION(BlueprintCallable, Category = "UI|Pooling")
	void EmptyPoolOfClass(const TSubclassOf<UUserWidget> WidgetClass);

	// Clears pools of all widgets, use with caution
	UFUNCTION(BlueprintCallable, Category = "UI|Pooling")
	void EmptyAllPools();

protected:
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, FPooledWidgetsData> WidgetPool;

	UUserWidget* FindFirstUnusedWidgetOfClass(TSubclassOf<UUserWidget> WidgetClass) const;

	UUserWidget* AddNewWidgetToPool(TSubclassOf<UUserWidget> WidgetClass);
	
};

