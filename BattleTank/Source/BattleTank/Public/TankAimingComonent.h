// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComonent.generated.h"

//Foward Decleration
class UTankBarrel; 
class UTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComonent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComonent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTurret* TurretToSet);

public:
	
	void AimAt(FVector HitLocation , float LaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;

	UTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

		
};
