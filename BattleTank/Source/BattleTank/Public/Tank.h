// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Foward Decleration
class UTankBarrel;  
class UTurret;
class UTankAimingComonent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
		void SetTurretReference(UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
		void FireTank();

	UPROPERTY(EditDefaultsOnly)
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 5000;  //Todo Find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComonent* TankAimingComponent = nullptr;


private:

	// Local barrel reference for firing
	UTankBarrel* Barrel = nullptr;

	float LastFiredTime = 0;

};

