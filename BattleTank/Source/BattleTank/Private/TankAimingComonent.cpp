// I have no copyright

#include "TankAimingComonent.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "BattleTank.h"



// Sets default values for this component's properties
UTankAimingComonent::UTankAimingComonent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComonent::BeginPlay()
{
	Super::BeginPlay();
	LastFiredTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComonent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (AmmoRemaining <= 0)
	{
		FireingStatus = EFiringStatus::Out;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFiredTime) < ReloadTimeInSeconds)
	{
		FireingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FireingStatus = EFiringStatus::Aiming;
	}
	else
	{
		FireingStatus = EFiringStatus::Locked;
	}
}


void UTankAimingComonent::Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	
}

void UTankAimingComonent::AimAt(FVector HitLocation)
{
	
	if (!ensure(Barrel)) { return; }  //protect against crashing

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));
	bool BHaveAimSoulution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		AimLaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (BHaveAimSoulution)
	{
		
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection); 
	}
}

int UTankAimingComonent::GetAmmoRemaining() const
{
	return AmmoRemaining;
}

EFiringStatus UTankAimingComonent::GetFireingState() const
{
	return FireingStatus;
}


bool UTankAimingComonent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return true; } // protect against crash

	FVector StartLocation = Barrel->GetForwardVector();

	return !StartLocation.Equals(AimDirection, 0.01);

}

void UTankAimingComonent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; } // protect against crash
	if (!ensure(Turret)) { return; } // protect against crash

	//Get desired rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}


void UTankAimingComonent::FireTank()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	if (FireingStatus != EFiringStatus::Reloading && FireingStatus != EFiringStatus::Out)
	{
		//Spawn projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>
			(ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("LaunchPoint")),
				Barrel->GetSocketRotation(FName("LaunchPoint"))
				);
		LastFiredTime = GetWorld()->GetTimeSeconds();
		projectile->LaunchProjectile(AimLaunchSpeed);
		AmmoRemaining = AmmoRemaining - 1;
	}
}

