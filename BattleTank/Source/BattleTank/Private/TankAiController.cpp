// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerState.h"
#include "TankAiController.h"
#include "BattleTank.h"		//needed for the tank

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp,Warning,TEXT("Ai is posessing %s :"), *(ControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Ai is not possesing a tank!"))
	}
}



ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
