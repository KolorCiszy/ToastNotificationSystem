
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

struct FToastPayloadData;
class UToastNotificationManager;

UCLASS()
class AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Toast Notifications")
	void Server_ContributeToVillageResources(const FToastPayloadData& ToastPayloadData);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UToastNotificationManager> ToastManager;
};