#pragma once
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Rotator.h"

struct FFramePackage
{
	FORCEINLINE FFramePackage();
	FORCEINLINE FFramePackage(FVector InLocation, FRotator InRotation, FVector InAngularVelocity, FVector InLinearVelocity, float InDeltaTime);

	FVector Location;
	FRotator Rotation;
	FVector AngularVelocity;
	FVector LinearVelocity;
	float DeltaTime;

	bool bIsPlayerPawn;
	FVector2D MouseXY;
};

FFramePackage::FFramePackage()
{
	
}

FFramePackage::FFramePackage(FVector InLocation, FRotator InRotation, FVector InAngularVelocity, FVector InLinearVelocity, float InDeltaTime):
	Location(InLocation), Rotation(InRotation), AngularVelocity(InAngularVelocity), LinearVelocity(InLinearVelocity), DeltaTime(InDeltaTime)
{

}