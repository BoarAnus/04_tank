// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerState.h"
#include "TankAiController.h"
#include "Tank.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"		//needed for the tank

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	
	if (PlayerTank)
	{
		//move twards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim Twards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//if ready
		//ControlledTank->FireTank(); //TODO limit fireing
	}
	
}
