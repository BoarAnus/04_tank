// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComonent.h"
#include "Engine/World.h"
#include "Engine.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/Class.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComonent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation , LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::FireTank()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE"))

		if (!Barrel) { return; }
	//Spawn projectile
	GetWorld()->SpawnActor<AProjectile>
		(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("LaunchPoint")),
			Barrel->GetSocketRotation(FName("LaunchPoint"))
		);
}

