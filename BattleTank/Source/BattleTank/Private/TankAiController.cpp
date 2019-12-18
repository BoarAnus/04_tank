// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerState.h"
#include "TankAiController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "BattleTank.h"		//needed for the tank

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	auto AiTank = GetControlledTank();
	if (!AiTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ai is not possesing a tank!"))
	}
	else 
	{
		if (!PlayerTank)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is possesing a tank but not aiming at anything"), *(AiTank->GetName()))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s :"), *(AiTank->GetName()), *(PlayerTank->GetName()))
		}
	}

}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO move twards player

		//Aim Twards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//if ready
			//fire
	}
	
}

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAiController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}else
	{
		return Cast<ATank>(PlayerPawn);
	}
}