// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"	
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void Tick(float DeltaTime) override;

	//start moving the barrel where the player is aiming
	void AimTowardsCrosshair();

	ATank* GetControlledTank() const;

	void BeginPlay() override;
};
