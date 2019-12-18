// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Math/UnrealMathUtility.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevationChange = FMath::Clamp<float>(RawNewElevation, MinBarrelElevation, MaxBarrelElevation);
	SetRelativeRotation(FRotator(ClampedElevationChange, 0, 0));

}