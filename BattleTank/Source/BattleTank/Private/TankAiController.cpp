// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h"
#include "GameFramework/PlayerState.h"
#include "TankAimingComonent.h"
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

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComonent>();

	if (PlayerTank)
	{
		//move twards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim Twards player
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (TankAimingComponent->GetFireingState() == EFiringStatus::Locked)
		{
			TankAimingComponent->FireTank(); //TODO limit fireing
		}
		
	}
	
}

void ATankAiController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnPosessedTankDeath);
		//Suscribe local method to the tanks death
	}
}

void ATankAiController::OnPosessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DEADDDDDD"));


}
