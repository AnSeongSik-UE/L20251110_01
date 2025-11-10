// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTarget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyTarget::AMyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MySphere(TEXT("/Script/Engine.StaticMesh'/Game/Mashes/SM_MySphere.SM_MySphere'"));
	if (SM_MySphere.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(SM_MySphere.Object);
	}
	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
	GetStaticMeshComponent()->SetCollisionProfileName(TEXT("OverlapAll"));

}

// Called when the game starts or when spawned
void AMyTarget::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AMyTarget::ProcessTakeAnyDamage);
}

// Called every frame
void AMyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyTarget::ProcessTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Damaged"));
	Destroy();
}
