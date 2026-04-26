// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPoolableWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UIPRACTICE_API IPoolableWidgetInterface
{
	GENERATED_BODY()
public:
	// Called automatically by the pool right before the widget is shown
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Pooling")
	void OnAcquiredFromPool();

	// Called automatically by the pool right after the widget is hidden
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI|Pooling")
	void OnReleasedToPool();
	
};
