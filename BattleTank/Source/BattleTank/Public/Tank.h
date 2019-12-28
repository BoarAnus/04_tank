// I have no copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Foward Decleration
class UTankBarrel;  
class UTurret;
class AProjectile;


UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	//UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitializeAIM(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
		void FireTank();

	UPROPERTY(EditDefaultsOnly)
		float ReloadTimeInSeconds = 3;  //FIRE
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;  //TODO remove when firing is out

	UPROPERTY(EditDefaultsOnly, Category = "Setup")  //FIRE
		TSubclassOf<AProjectile> ProjectileBlueprint;

private:
	void BeginPlay() override;

	// Local barrel reference for firing
	UTankBarrel* Barrel = nullptr;  //TODO remove

	float LastFiredTime = 0;  //Fire

};

