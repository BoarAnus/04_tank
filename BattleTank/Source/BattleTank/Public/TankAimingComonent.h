// I have no copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComonent.generated.h"

// Enum for aiming states
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Foward Declerations
class UTankBarrel; 
class UTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComonent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet);
	
	void AimAt(FVector HitLocation);


private:
	// Sets default values for this component's properties
	UTankAimingComonent();

	UTankBarrel* Barrel = nullptr;

	UTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AimLaunchSpeed = 50000.f;

	void MoveBarrelTowards(FVector AimDirection);

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FireingStatus = EFiringStatus::Locked;

};
