// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FramePackage.h"

#include "ReverseTimeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class REVERSETIME_API UReverseTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReverseTimeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void SetReversingTime(bool InReversingTime);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	bool bReversingTime; // Set to true to reverse time

	bool bOutOfData; // Set to true when there is no more data to reverse time with

	float RunningTime;  // The time that has passed since the player started reversing time

	float ReverseRunningTime; // The time of the frame package delta time

	float RecordedTime; 

	TDoubleLinkedList<FFramePackage> StoredFrames; // The list of frame packages that are stored
};
