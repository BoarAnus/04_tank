// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/Vector.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"

#include "DrawDebugHelpers.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormanImpulse, const FHitResult& Hit)
{
	//Drive tracks
	//apply sideways force
	ApplySidewaysForce();
}


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UTankTrack::ApplySidewaysForce()
{

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	//Calculate slippage speed crossproduct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work out required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculate and aplly sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce);
	// f=ma
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,+1);
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTrack::DriveTrack()
{
	//TODO Clamp player throttle value 
	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }  //pointer protection
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);


}

