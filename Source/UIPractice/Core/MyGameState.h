// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UIPractice/UI/ToastNotificationSystem/ToastPayloadData.h"
#include "MyGameState.generated.h"

class AMyPlayerController;
UCLASS()
class UIPRACTICE_API AMyGameState : public AGameStateBase
{

	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, BlueprintAuthorityOnly, meta=(AutoCreateRefTerm="ToastData"), Category = "Networking|UI")
	void Multicast_DispatchGlobalToastEvent(const FToastPayloadData& ToastData);
};
