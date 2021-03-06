// I have no copyright

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);  //needed to enable events on damage

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//Returns currentHealth between 0 and 1 percentage
	UFUNCTION(BlueprintPure,Category = "Health")
	float GetHealthPercent() const;
	
	//Called by the engine when damage is delt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	FTankDelegate OnDeath;

private:
	void BeginPlay() override;
	
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 TankStartingHealth = 100;

	int32 TankHealth = TankStartingHealth;
};

