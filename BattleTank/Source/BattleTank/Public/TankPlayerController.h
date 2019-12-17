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

	bool GetSightRayHitLocation( FVector& Hitlocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	

};
