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
	UE_LOG(LogTemp,Warning, TEXT("im hit!"))
}


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

}
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Calculate slippage speed crossproduct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work out required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculate and aplly sideways force
	auto TankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent());

	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	
	TankRoot->AddForce(CorrectionForce);
	// f=ma

}

void UTankTrack::SetThrottle(float Throttle)
{
		//TODO Clamp player throttle value 
	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }  //pointer protection
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	
}


