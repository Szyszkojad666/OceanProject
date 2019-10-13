// 2016 - Community based open project


#include "Boat.h"
#include "BuoyancyForceComponent.h"
#include "OceanManager.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoatMovementComponent.h"
#include "Camera/CameraComponent.h"
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
	
	EngineLocation = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("EngineLocation"));
	EngineLocation->SetupAttachment(StaticMesh);

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
}

bool ABoat::IsEngineBelowSeaLevel()
{
	if (BuoyancyForce && BoatMovement)
	{
		if (OceanManager)
		{
			float WaveHeight = OceanManager->GetWaveHeight(GetActorLocation());
			float EngineHeight = BoatMovement->GetForceLocation().Z;
			return WaveHeight >= EngineHeight;
		}
	}
	return true;
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
		PlayerInputComponent->BindAxis("MoveForward",this, &ABoat::MoveRight);
	}
}

void ABoat::MoveRight(float Value)
{
	if (IsEngineBelowSeaLevel())
	BoatMovement->MoveRight(Value);
}

void ABoat::MoveForward(float Value)
{
	if (IsEngineBelowSeaLevel())
	BoatMovement->MoveForward(Value);
}

