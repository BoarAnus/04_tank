// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
		//TODO Clamp player throttle value 
	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!TankRoot)
	{
		UE_LOG(LogTemp,Warning,TEXT("NO TRACK AT TANKROOT"))
	}
	else
	{
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}
