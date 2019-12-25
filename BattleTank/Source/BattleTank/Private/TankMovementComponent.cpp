// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/Vector.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveFoward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	// No Need to call Super:: because we are replaceing the whole thing

	auto TankFoweward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AiForewardIntention = MoveVelocity.GetSafeNormal();
	auto StickThrow = FVector::DotProduct(TankFoweward, AiForewardIntention);

	IntendMoveFoward(StickThrow);
	
	
	// UE_LOG(LogTemp, Warning, TEXT("%s is trying to move to %s"), *TankName, *MoveVelocityString);

}
