// 2016 - Community based open project


#include "Boat.h"
//#include "OceanPlugin/Classes/BuoyancyForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoatMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABoat::ABoat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	BoatMovement = CreateDefaultSubobject<UBoatMovementComponent>(TEXT("BoatMovement"));
	//BuoyancyForce = CreateDefaultSubobject<UBuoyancyForceComponent>(TEXT("BuoyancyForce"));
	EngineLocation = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("EngineLocation"));
	EngineLocation->SetupAttachment(RootComponent);
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 500;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);
}

// Called when the game starts or when spawned
void ABoat::BeginPlay()
{
	Super::BeginPlay();
	
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
	BoatMovement->MoveRight(Value);
}

void ABoat::MoveForward(float Value)
{
	BoatMovement->MoveForward(Value);
}

