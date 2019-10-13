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

void UBoatMovementComponent::SetForceLocationFromPrimitveComp(UPrimitiveComponent * PrimitiveComponent)
{
	 PrimitiveForceLocation = PrimitiveComponent;
}

// Called every frame
void UBoatMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AddDrivingForce(DeltaTime);
	
	// ...
}

FVector UBoatMovementComponent::GetForceLocation()
{
	return PrimitiveForceLocation ? PrimitiveForceLocation->GetComponentLocation() : FVector(0,0,0);
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
	
	UStaticMeshComponent* OwnerMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (OwnerMesh)
	{
		FVector ForceLocation = !PrimitiveForceLocation ? OwnerMesh->GetComponentLocation() : PrimitiveForceLocation->GetComponentLocation();
		ApplyRotation(DeltaTime, SteeringThrow);
		OwnerMesh->AddForceAtLocation(Force, ForceLocation, NAME_None);
	}
}

void UBoatMovementComponent::ApplyRotation(float DeltaTime, float Rotation)
{
	if (FMath::Abs(Rotation) > 0.0f)
	{
		float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), GetOwner()->GetVelocity() / 100);
		//float RateOfTurn = GetOwner()->GetVelocity().Size() /100 / TurningCircleRadius;
		float RateOfTurn = DeltaLocation / TurningCircleRadius;
		float DTheta = (RateOfTurn * Rotation * DeltaTime);
		FQuat DeltaRotation(FVector(0,0,1), DTheta);
		GetOwner()->AddActorWorldRotation(DeltaRotation);
		
		UE_LOG(LogTemp, Warning, TEXT("Up Vector is %s"), *GetOwner()->GetActorUpVector().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Rate of turn is %f"), RateOfTurn);
	}
}

