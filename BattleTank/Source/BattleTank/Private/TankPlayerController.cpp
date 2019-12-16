// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Make sure all preveus code gets called
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp,Warning,TEXT("Player Controlling: %s "), *(ControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Player is not poseeseong a tank "))
	}
	

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
