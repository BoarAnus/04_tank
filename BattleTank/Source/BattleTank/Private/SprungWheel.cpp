// I have no copyright


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint = CreateDefaultSubobject < UPhysicsConstraintComponent>(FName("Physics Constraint Component"));
	SetRootComponent(PhysicsConstraint);
	

	BodyObject = CreateDefaultSubobject <UStaticMeshComponent>(FName("Body Object"));
	BodyObject->SetupAttachment(PhysicsConstraint);
	
	WheelObject = CreateDefaultSubobject <UStaticMeshComponent>(FName("Wheel Object"));
	WheelObject->SetupAttachment(PhysicsConstraint);

	
	
	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

