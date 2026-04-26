// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlideAnimatorWidget.generated.h"


UENUM(BlueprintType)
enum class ESlideDirection : uint8
{
	UpToDown,
	DownToUp,
	LeftToRight,
	RightToLeft
};

class UNamedSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimatorFinishedSignature);
/**
 * 
 */
UCLASS(Abstract)
class UIPRACTICE_API USlideAnimatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USlideAnimatorWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Slide Amimator")
	void PlaySlideIn();

	UFUNCTION(BlueprintCallable, Category = "Slide Amimator")
	void PlaySlideOut();
	
	UPROPERTY(BlueprintAssignable, Category = "Slide Amimator")
	FOnAnimatorFinishedSignature OnSlideOutFinished;

	UPROPERTY(BlueprintAssignable, Category = "Slide Amimator")
	FOnAnimatorFinishedSignature OnSlideInFinished;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Slide Amimator")
	UNamedSlot* ContentSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Amimator", meta = (ExposeOnSpawn = "true"))
	ESlideDirection SlideDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Amimator", meta = (ExposeOnSpawn = "true"))
	float SlideDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Amimator", meta = (ExposeOnSpawn = "true", ClampMin = "0.01"))
	float SlideDuration;
	
private:
	float CurrentAlpha;
	
	float TargetAlpha;
	
	bool bIsAnimating;
	
	void UpdateRenderTransformAndOpacity();
};
