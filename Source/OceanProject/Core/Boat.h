// 2016 - Community based open project

#pragma once

#include "OceanProject.h"
#include "GameFramework/Pawn.h"
#include "Boat.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UBuoyancyForceComponent;
class UBoatMovementComponent;
class UArrowComponent;
class UCameraComponent;
class UBoxComponent;
class AOceanManager;




UCLASS()
class OCEANPROJECT_API ABoat : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoat();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBuoyancyForceComponent* BuoyancyForce;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoatMovementComponent* BoatMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UArrowComponent* EngineLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* BoatDB;

	UPROPERTY(EditDefaultsOnly)
	FName BoatDBName;

	UFUNCTION(BlueprintCallable)
	bool IsEngineBelowSeaLevel();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetMovementParameters(float BoatMass, float DrivingForce, float TurningRadius, float AirDragCoefficient);
	
	virtual void Tick(float DeltaTime) override;

	FBoatInfo* BoatInfo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AOceanManager* OceanManager = nullptr;

private:
	
	void MoveRight(float Value);

	void MoveForward(float Value);

};
