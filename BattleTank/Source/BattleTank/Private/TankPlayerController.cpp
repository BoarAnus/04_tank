// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "DrawDebugHelpers.h" //drawdebughelpers wont be needed later
#include "GameFramework/PlayerController.h"
#include "Math/Vector.h"
#include "Engine/World.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Make sure all preveus code gets called
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlling: %s "), *(ControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Player is not poseeseong a tank "))
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
	
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; } //protect engine from crashing
	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) //Get world locations of linetrace through crosshair
	{
		GetControlledTank()->AimAt(HitLocation);	
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
		ECollisionChannel::ECC_Visibility
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

