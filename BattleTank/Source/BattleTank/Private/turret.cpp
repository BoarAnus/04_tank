// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "BattleTank.h"
#include "Math/UnrealMathUtility.h"


/*
	auto TimeLog = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f -- We are getting this far!"), TimeLog);
*/

void UTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewAzimuth = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0,RawNewAzimuth, 0));

}