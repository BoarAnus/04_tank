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
	

private:
	void BeginPlay() override;

	
};

