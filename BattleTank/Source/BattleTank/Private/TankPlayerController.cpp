// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "GameFramework/PlayerState.h"
#include "TankAimingComonent.h"
#include "Math/Vector.h"
#include "Engine/World.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Make sure all preveus code gets called
	auto AimingComponent =GetPawn()->FindComponentByClass<UTankAimingComonent>();
	if (!ensure(AimingComponent)) { return; }  //Pointer Protection
	FoundAimingComponent(AimingComponent);  //Call Blueprint to setup retcile
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
	
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // crash protection

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) //Get world locations of linetrace through crosshair
	{
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComonent>();
		if (!ensure(AimingComponent)) { return; }  //Pointer Protection
		AimingComponent->AimAt(HitLocation);
	}
	
}

// FVector HitLocation is OUT var
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// Deproject screen position fo crosshair to world direction
	FVector PlayerLookDirection;
	if (GetLookDirection(ScreenLocation, PlayerLookDirection))
	{
		//line trace along look direction see what we hit, up to max range
		return GetLookVectorHitLocation(PlayerLookDirection, HitLocation);
	}
	else
	{
		return false;
	}
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; //To Be Discarded
	FVector LookRotation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + (LookDirection * LineTraceRange);
	FHitResult HitResult;  //HitResults
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECollisionChannel::ECC_Camera
		))
		{
		HitLocation = HitResult.Location;
			return true;
		}
	else
	{
		return false;
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPosessedTankDeath);
	}
}

void ATankPlayerController::OnPosessedTankDeath()
{
	StartSpectatingOnly();
	UE_LOG(LogTemp, Warning, TEXT("Player DEADDDDDD"));
}

