// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

#include "MyPlayerController.h"
#include "UIPractice/UI/ToastNotificationSystem/ToastNotificationManager.h"

void AMyGameState::Multicast_DispatchGlobalToastEvent_Implementation(const FToastPayloadData& ToastData)
{
	auto TrySendToastForPlayer = [&](const AMyPlayerController* Player)
	{
		if (!Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to send toast notification, PlayerContr is nullptr"));
		}
		
		if (const auto ManagerComp = Player->GetComponentByClass<UToastNotificationManager>())
		{
			ManagerComp->Client_AddToastNotificationToQueue(ToastData);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to send toast notification, %s is missing a ToastManagerComponent"), *Player->GetName());
		}
	};
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AMyPlayerController* ConnectedPC = Cast<AMyPlayerController>(It->Get());
		TrySendToastForPlayer(ConnectedPC);
	}
}
