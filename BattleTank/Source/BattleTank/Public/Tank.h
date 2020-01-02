// I have no copyright

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"


UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	//Called by the engine when damage is delt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	

private:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 TankStartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	int32 TankHealth = TankStartingHealth;
};

