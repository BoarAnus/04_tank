// I have no copyright

#include "TankAimingComonent.h"
#include "Engine/World.h"
#include "Engine.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/Class.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = FindComponentByClass<UTankAimingComonent>();
	UE_LOG(LogTemp,Warning,TEXT(" %s tank aiming component "),*TankAimingComponent->GetName())
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }	//Protect against crash

	TankAimingComponent->AimAt(HitLocation , LaunchSpeed);
}

void ATank::InitializeAIM(UTankBarrel* BarrelToSet, UTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	//TankAimingComponent->Initialize(BarrelToSet, TurretToSet);
}


void ATank::FireTank()
{
	bool IsReloaded =  (GetWorld()->GetTimeSeconds() - LastFiredTime) > ReloadTimeInSeconds;
	
	if (Barrel && IsReloaded)
	{
		//Spawn projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>
			(ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("LaunchPoint")),
				Barrel->GetSocketRotation(FName("LaunchPoint"))
				);
		LastFiredTime = GetWorld()->GetTimeSeconds();
		projectile->LaunchProjectile(LaunchSpeed);
	}
}

