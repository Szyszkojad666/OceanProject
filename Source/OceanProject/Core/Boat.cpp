// 2016 - Community based open project


#include "Boat.h"
#include "BuoyancyForceComponent.h"
#include "OceanManager.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoatMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
ABoat::ABoat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetSimulatePhysics(true);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoatMovement = CreateDefaultSubobject<UBoatMovementComponent>(TEXT("BoatMovement"));
	
	BuoyancyForce = CreateDefaultSubobject<UBuoyancyForceComponent>(TEXT("BuoyancyForce"));

	EngineLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("EngineLocation"));
	BoatMovement->SetForceLocationFromPrimitveComp(EngineLocation);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(StaticMesh);
	CameraSpringArm->TargetArmLength = 500;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);
}

// Called when the game starts or when spawned
void ABoat::BeginPlay()
{
	Super::BeginPlay();
	OceanManager = BuoyancyForce->OceanManager;
	if (BoatDB)
	{
		BoatInfo = BoatDB->FindRow<FBoatInfo>(BoatDBName, "");
		SetMovementParameters(BoatInfo->BoatMass, BoatInfo->MaxDrivingForce, BoatInfo->TurningCircleRadius, BoatInfo->DragCoefficient);
	}
}

bool ABoat::IsEngineBelowSeaLevel()
{
	if (BuoyancyForce && BoatMovement)
	{
		if (OceanManager)
		{
			bool IsEngineBelowSeaLevel;
			float WaveHeight = OceanManager->GetWaveHeight(GetActorLocation());
			float EngineHeight = BoatMovement->GetForceLocation().Z;
			IsEngineBelowSeaLevel = WaveHeight >= EngineHeight;
			UE_LOG(LogTemp, Warning, TEXT("Wave height is %d, Engine Height is %d"), WaveHeight, EngineHeight);
			return IsEngineBelowSeaLevel;
		}
	}
	return true;
}

void ABoat::SetMovementParameters(float BoatMass, float DrivingForce, float TurningRadius, float AirDragCoefficient)
{
	BoatMovement->SetMovementParameters(BoatMass, DrivingForce, TurningRadius, AirDragCoefficient);
}

// Called every frame
void ABoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward",this, &ABoat::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight",this, &ABoat::MoveRight);
	}
}

void ABoat::MoveRight(float Value)
{
		BoatMovement->MoveRight(Value);
}

void ABoat::MoveForward(float Value)
{
		BoatMovement->MoveForward(Value);
}

