// I have no copyright


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	AxleConstraint = CreateDefaultSubobject <UPhysicsConstraintComponent>(FName("Axle Physics component"));
	SetRootComponent(AxleConstraint);

	AxleObject = CreateDefaultSubobject	<UStaticMeshComponent>(FName("Axle Object"));
	AxleObject->SetupAttachment(AxleConstraint);

	WheelConstraint = CreateDefaultSubobject < UPhysicsConstraintComponent>(FName("Wheel Constraint Component"));
	WheelConstraint->SetupAttachment(AxleObject);

	WheelObject = CreateDefaultSubobject <UStaticMeshComponent>(FName("Wheel Object"));
	WheelObject->SetupAttachment(AxleObject);
	

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	WheelObject->SetNotifyRigidBodyCollision(true);
	WheelObject->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	

	SetupConstraints();
	
}



// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ForceMagnigudeThisFrame = 0.f;

}

void ASprungWheel::AddDrivingForce(float ForceMagnigude)
{
	ForceMagnigudeThisFrame += ForceMagnigude;

}


void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	
	AxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, AxleObject, NAME_None);
	WheelConstraint->SetConstrainedComponents(AxleObject, NAME_None, WheelObject, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	WheelObject->AddForce(AxleObject->GetForwardVector() * ForceMagnigudeThisFrame);
	
}

