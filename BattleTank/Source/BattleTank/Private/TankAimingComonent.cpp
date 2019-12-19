// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "BattleTank.h"
#include "Containers/Array.h"
#include "TankAimingComonent.h"

// Sets default values for this component's properties
UTankAimingComonent::UTankAimingComonent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComonent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }  //protect against crashing
	Barrel = BarrelToSet;
}

void UTankAimingComonent::SetTurretReference(UTurret* TurretToSet)
{
	if (!TurretToSet) { return; }  //protect against crashing
	Turret = TurretToSet;
}
void UTankAimingComonent::AimAt(FVector HitLocation ,  float LaunchSpeed)
{
	if (!Barrel) { return; }  //protect against crashing

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));
	bool BHaveAimSoulution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (BHaveAimSoulution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection); 
		
	}else
	{
		
	}

	

}

void UTankAimingComonent::MoveBarrelTowards(FVector AimDirection)
{
	//Get desired rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	

	//get desired elevation
	//Get current rotation
	//get cuttent elevation


	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);



	//if current elevation is desired elevation
		//do nothing
	//else move barrel

	//if current rotation is desired rotation
		// do nothing
	//else move barrel
}

