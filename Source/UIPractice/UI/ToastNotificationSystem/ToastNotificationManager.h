// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToastPayloadData.h"
#include "Components/ActorComponent.h"
#include "ToastNotificationManager.generated.h"

struct FToastPayloadData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToastQueueEntryAddedSignature);

/*
 * This class manages toast notification queue
 * Possible implementation extension: make new toast notifications "refresh" existing ones if they have the same message and icon
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UIPRACTICE_API UToastNotificationManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UToastNotificationManager();

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_AddToastNotificationToQueue(const FToastPayloadData& Data);

	UFUNCTION(BlueprintCallable)
	bool DequeueMostRecentToastNotification(FToastPayloadData& DequeuedData);
	
	UPROPERTY(BlueprintAssignable)
	FOnToastQueueEntryAddedSignature OnToastQueueEntryAddedDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// We can use a queue here since this doesn't hold UObject ptrs, in which case we would probably want a UPROPERTY TArray<>
	TQueue<FToastPayloadData> ToastQueue;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

