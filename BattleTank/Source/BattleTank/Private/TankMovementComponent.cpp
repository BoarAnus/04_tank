// I have no copyright

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Math/Vector.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

// Intend to move foward. positive is foreward
void UTankMovementComponent::IntendMoveFoward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }	//pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

// intend to turn. positive is right
void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }	//pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	// No Need to call Super:: because we are replaceing the whole thing

	auto TankFoweward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AiForewardIntention = MoveVelocity.GetSafeNormal();
	auto TrottleStickThrow = FVector::DotProduct(TankFoweward, AiForewardIntention);

	auto TurnStickThrow = FVector::CrossProduct(TankFoweward, AiForewardIntention ).Z;
	
	IntendTurn(TurnStickThrow);
	IntendMoveFoward(TrottleStickThrow);
	
	// UE_LOG(LogTemp, Warning, TEXT("%s is trying to move to %s"), *TankName, *MoveVelocityString);
}
