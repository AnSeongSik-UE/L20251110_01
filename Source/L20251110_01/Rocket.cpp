// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(30.f, 10.f, 10.f));

	Rocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	Rocket->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Mashes/SM_Rocket.SM_Rocket'"));
	if (SM_Rocket.Succeeded())
	{
		Rocket->SetStaticMesh(SM_Rocket.Object);
		Rocket->SetRelativeRotation(FRotator(-90.f, 0, 0));
	}

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 2000.f;
	Movement->MaxSpeed = 2000.f;
	Movement->ProjectileGravityScale = 0;
	Rocket->SetRelativeRotation(FRotator(-90.f, 0, 0));
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	//SetLifeSpan(3.f);

	FLatentActionInfo Info;
	Info.ExecutionFunction = TEXT("Timeout");
	Info.CallbackTarget = this;
	Info.Linkage = 1;
	Info.UUID = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 1.0f, Info);

	//Delegate UE
	OnActorBeginOverlap.AddDynamic(this, &ARocket::ProcessActorBeginOverlap);
	//OnActorBeginOverlap.Remove(this, TEXT("ProcessActorBeginOverlap"));
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocket::Timeout()
{
	//UE_LOG(LogTemp, Warning, TEXT("Died"));
	Destroy();
}

void ARocket::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OverLapped"));
	UGameplayStatics::ApplyDamage(OtherActor, 10.0f, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, nullptr);
}

