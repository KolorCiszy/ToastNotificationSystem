// Fill out your copyright notice in the Description page of Project Settings.


#include "ToastNotificationManager.h"
#include "ToastPayloadData.h"

// Sets default values for this component's properties
UToastNotificationManager::UToastNotificationManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UToastNotificationManager::Client_AddToastNotificationToQueue_Implementation(const FToastPayloadData& Data)
{
	ToastQueue.Enqueue(Data);
	OnToastQueueEntryAddedDelegate.Broadcast();
}

void UToastNotificationManager::BeginPlay()
{
	Super::BeginPlay();
}

void UToastNotificationManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UToastNotificationManager::DequeueMostRecentToastNotification(FToastPayloadData& DequeuedData)
{
	return ToastQueue.Dequeue(DequeuedData);
}
