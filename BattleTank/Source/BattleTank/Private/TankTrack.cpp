// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
		//TODO Clamp player throttle value 
	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}
