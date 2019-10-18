#pragma once
#include "Engine/DataTable.h"
#include "StructsAndEnums.generated.h"

USTRUCT(BlueprintType)
struct FBoatInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	// It's also data base ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoatName;
	
	//In kilograms
	UPROPERTY(EditAnywhere)
	float BoatMass;

	//How strong the engines are
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce;

	//In metres
	UPROPERTY(EditAnywhere)
	float TurningCircleRadius;

	//How aerodynamic the boat is
	UPROPERTY(EditAnywhere)
	float DragCoefficient;

	//In cubic metres
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CargoSpace;

	//How much the boat with of all its passengers, fuel and cargo can weigh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxTonnage;

	//Each passenger on board adds 80kgs
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PassengerSeats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HullStrength;
	
	//In Litres, adds mass
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Fuel;
};