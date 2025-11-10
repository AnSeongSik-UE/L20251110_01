// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPC.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

AMyPC::AMyPC()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Default.IMC_Default'"));
	if (IMC_Default.Succeeded())
	{
		InputMapping = IMC_Default.Object;
	}
}

void AMyPC::BeginPlay()
{
	Super::BeginPlay();

	//ULocalPlayer* LocalPlayer = GetLocalPlayer();
	//ULocalPlayerSubsystem* MySubsystem = LocalPlayer->GetSubsystem<UMyPlayerSubsystem>();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}

}
