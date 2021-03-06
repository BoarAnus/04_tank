// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downword speed +1 is max upword speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 20.f;  
	//In degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxBarrelElevation = 35.f;  
	//In degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinBarrelElevation = -0.95;  
};
