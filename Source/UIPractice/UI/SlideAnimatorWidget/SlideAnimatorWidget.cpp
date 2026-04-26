// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideAnimatorWidget.h"
#include "Components/NamedSlot.h"
#include "Math/UnrealMathUtility.h"

USlideAnimatorWidget::USlideAnimatorWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, SlideDirection(ESlideDirection::UpToDown)
	, SlideDistance(100.0f)
	, SlideDuration(0.3f)
	, bIsAnimating(false)
	, CurrentAlpha(0.0f)
	, TargetAlpha(0.0f)
{
}

void USlideAnimatorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bIsAnimating) return;
	
	const float AlphaStep = InDeltaTime / FMath::Max(0.01f, SlideDuration);

	if (CurrentAlpha < TargetAlpha)
	{
		CurrentAlpha = FMath::Min(CurrentAlpha + AlphaStep, TargetAlpha);
	}
	else if (CurrentAlpha > TargetAlpha)
	{
		CurrentAlpha = FMath::Max(CurrentAlpha - AlphaStep, TargetAlpha);
	}
	
	UpdateRenderTransformAndOpacity();

	if (CurrentAlpha == TargetAlpha)
	{
		bIsAnimating = false;
		
		if (TargetAlpha == 0.0f)
		{
			OnSlideOutFinished.Broadcast();
		}
		else
		{
			OnSlideInFinished.Broadcast();
		}
	}
}

void USlideAnimatorWidget::PlaySlideIn()
{
	if (CurrentAlpha == 1.0f) 
	{
		CurrentAlpha = 0.0f;
	}
	
	TargetAlpha = 1.0f;
	bIsAnimating = true;
}

void USlideAnimatorWidget::PlaySlideOut()
{
	TargetAlpha = 0.0f;
	bIsAnimating = true;
}

void USlideAnimatorWidget::UpdateRenderTransformAndOpacity()
{
	const float EasedAlpha = FMath::SmoothStep(0.0f, 1.0f, CurrentAlpha);
	
	FVector2D HiddenOffset = FVector2D::ZeroVector;
	switch (SlideDirection)
	{
	case ESlideDirection::UpToDown:	HiddenOffset.Y = -SlideDistance;
		break;
	case ESlideDirection::DownToUp:	HiddenOffset.Y = SlideDistance;
		break;
	case ESlideDirection::LeftToRight:	HiddenOffset.X = -SlideDistance;
		break;
	case ESlideDirection::RightToLeft:	HiddenOffset.X = SlideDistance;
		break;
	}
	
	const FVector2D NewTranslation = FMath::Lerp(HiddenOffset, FVector2D::ZeroVector, EasedAlpha);
	
	if (ContentSlot)
	{
		ContentSlot->SetRenderTranslation(NewTranslation);
		ContentSlot->SetRenderOpacity(EasedAlpha);
	}
	else
	{
		SetRenderTranslation(NewTranslation);
		SetRenderOpacity(EasedAlpha);
	}
}
