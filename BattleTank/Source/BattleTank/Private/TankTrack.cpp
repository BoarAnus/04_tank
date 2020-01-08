// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Math/Vector.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
		//UE_LOG(LogTemp, Warning, TEXT("Found wheel %s"), *SprungWheel->GetName());

	}
	return ResultArray;
}



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle,-1,+1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//TODO Clamp player throttle value 
	auto ForceApplied = CurrentThrottle * MaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}


}

