// Fill out your copyright notice in the Description page of Project Settings.


#include "P38.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Rocket.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AP38::AP38()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(46.f, 70.f, 15.f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Mashes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.f, -21.f, 1.f));
	
	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.f, 21.f, 1.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/Mashes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->TargetArmLength = 150.f;
	SpringArm->SocketOffset = FVector(0, 0, 50.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bDoCollisionTest = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(70.f, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 100.f;
	Movement->Acceleration = 4000.f;
	Movement->Deceleration = 8000.f;
}

// Called when the game starts or when spawned
void AP38::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP38::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());
	
	Left->AddRelativeRotation(FRotator(0, 0, 10.f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
	Right->AddRelativeRotation(FRotator(0, 0, 10.f * DeltaTime));
}

// Called to bind functionality to input
void AP38::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AP38::Fire);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AP38::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AP38::Roll);
}

void AP38::Fire()
{
	GetWorld()->SpawnActor<ARocket>(ARocket::StaticClass(),
		Arrow->GetComponentToWorld());
}

void AP38::Pitch(float Value)
{
	AddActorLocalRotation(
		FRotator(
			Value * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			0,
			0));
}

void AP38::Roll(float Value)
{
	AddActorLocalRotation(
		FRotator(
			0,
			0,
			Value * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}
