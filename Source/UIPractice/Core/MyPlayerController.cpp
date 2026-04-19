#include "MyPlayerController.h"

#include "MyGameState.h"
#include "UIPractice/UI/ToastNotificationSystem/ToastNotificationManager.h"

AMyPlayerController::AMyPlayerController()
{
	ToastManager = CreateDefaultSubobject<UToastNotificationManager>(TEXT("ToastManagerComponent"));
	
}

void AMyPlayerController::Server_ContributeToVillageResources_Implementation(const FToastPayloadData& ToastPayloadData)
{
	/* For testing purposes this function skips validating data (if player can actually do this)
	* and goes straight into sending the notification
	* In a real game we would like to call a request to modify village resources and if the server allows us to, then send the notification
	*/

	if (AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>())
	{
		GS->Multicast_DispatchGlobalToastEvent(ToastPayloadData);
	}
}
