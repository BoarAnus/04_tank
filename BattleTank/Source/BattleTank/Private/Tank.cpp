// I have no copyright

#include "Tank.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "Engine.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	float DamageToApply = FMath::Clamp<int>(DamagePoints, 0, TankHealth);
	
	TankHealth = TankHealth - DamageToApply;

	if (TankHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Dead! BURRRRN!"));
	}
	

	return DamageToApply;
}


float ATank::GetHealthPercent() const
{
	return (float)TankHealth / (float)TankStartingHealth;
}

