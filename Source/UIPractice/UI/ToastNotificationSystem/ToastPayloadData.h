#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "ToastPayloadData.generated.h"

USTRUCT(BlueprintType)
struct FToastNotificationIconData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Tint;
};


UENUM(BlueprintType)
enum class EToastNotificationType : uint8 
{
	Info, Warning, Error, Reward
};

USTRUCT(BlueprintType)
struct FToastPayloadData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast")
	EToastNotificationType Severity = EToastNotificationType::Info;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast")
	FGameplayTag IconID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast")
	FText LocalizedMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast")
	double Value = 0.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toast")
	bool bShowValueText = false;
};
