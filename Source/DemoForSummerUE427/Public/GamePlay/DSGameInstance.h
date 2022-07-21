// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMOFORSUMMERUE427_API UDSGameInstance : public UGameInstance
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, Category = "DemoSummer")
		FString GameName;
};
