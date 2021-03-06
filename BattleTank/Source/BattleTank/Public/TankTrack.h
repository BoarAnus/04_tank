// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set max driving force and apply forces to the tank
 */

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);


private:
	//Max force per track in neutons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDrivingForce = 40000000.f;

	virtual void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels() const;

	UTankTrack();

	void DriveTrack(float CurrentThrottle);

};
