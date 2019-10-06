// 2016 - Community based open project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoatMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OCEANPROJECT_API UBoatMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoatMovementComponent();

	void MoveRight(float Value);
	void MoveForward(float Value);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
private:
		
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	UPROPERTY(EditAnywhere)
	float MaxRotation = 90;

	UPROPERTY(EditAnywhere)
	float TurningCircleRadius = 11;

	//How aerodynamic the boat is
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	FVector AccelerationForce;

	float SteeringThrow;

	float Throttle;

	FVector CalculateAirResistance();

	void AddDrivingForce(float DeltaTime);

	void ApplyRotation(float DeltaTime, float SteeringThrow);
};
