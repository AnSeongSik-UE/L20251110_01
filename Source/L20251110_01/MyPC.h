// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPC.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class L20251110_01_API AMyPC : public APlayerController
{
	GENERATED_BODY()
	AMyPC();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	virtual void BeginPlay() override;
};