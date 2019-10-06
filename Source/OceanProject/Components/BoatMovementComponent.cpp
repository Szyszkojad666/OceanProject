// 2016 - Community based open project


#include "BoatMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UBoatMovementComponent::UBoatMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoatMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UBoatMovementComponent::MoveRight(float Value)
{
	SteeringThrow = Value;
}

void UBoatMovementComponent::MoveForward(float Value)
{
	Throttle = Value;
}

// Called every frame
void UBoatMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AddDrivingForce(DeltaTime);
	
	// ...
}

FVector UBoatMovementComponent::CalculateAirResistance()
{
	float AirResistanceMagnitude = -pow(GetOwner()->GetVelocity().Size(), 2) * DragCoefficient;
	FVector AirResistanceVector = GetOwner()->GetVelocity().GetSafeNormal() * AirResistanceMagnitude;
	return AirResistanceVector;
}

void UBoatMovementComponent::AddDrivingForce(float DeltaTime)
{
	FVector Force = GetOwner()->GetActorForwardVector() * Throttle * MaxDrivingForce;
	Force += CalculateAirResistance();
	FVector Acceleration = Force / Mass;
	AccelerationForce = AccelerationForce + Acceleration * DeltaTime;

	UStaticMeshComponent* OwnerMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (OwnerMesh)
	{
		FVector ForceLocation =OwnerMesh->GetComponentLocation();
		OwnerMesh->AddForceAtLocation(AccelerationForce, ForceLocation, NAME_None);
		ApplyRotation(DeltaTime, SteeringThrow);
	}
}

void UBoatMovementComponent::ApplyRotation(float DeltaTime, float Rotation)
{
	float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), AccelerationForce) * DeltaTime; // Dot Products gives you the proportion of how close one Vector is to another
	float DTheta = (DeltaLocation / TurningCircleRadius) * Rotation;
	FQuat DeltaRotation(GetOwner()->GetActorUpVector(), DTheta);
	GetOwner()->AddActorWorldRotation(DeltaRotation);
}

