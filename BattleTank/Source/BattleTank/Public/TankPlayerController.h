// I have no copyright
#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


//Foward declairations 
class ATank;
class UTankAimingComonent;

/**
 *   Responsable for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComonent* AimCompRef);

private:
	virtual void Tick(float DeltaTime) override;

	//start moving the barrel where the player is aiming
	void AimTowardsCrosshair();

	void BeginPlay() override;

	bool GetSightRayHitLocation( FVector& Hitlocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	UFUNCTION()
	void OnPosessedTankDeath();
	

};
