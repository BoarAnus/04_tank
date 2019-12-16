// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/PlayerState.h"
//drawdebughelpers wont be needed later
#include "DrawDebugHelpers.h"
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
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("hitlocation : %s"), *(HitLocation.ToString()))


			//Get world locations of linetrace through crosshair
			//if hits lanscape
				//tell controlled tank to aim at this point
	}
}

// FVector HitLocation is OUT var
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find crosshair position in pixel location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	

	// Deproject screen position fo crosshair to world direction
	//line trace along look direction see what we hit, up to max range
	return true;
}


