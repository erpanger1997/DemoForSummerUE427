// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEMOFORSUMMERUE427_API ADSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADSGameMode();

	virtual void Tick(float DeltaSeconds) override;

	void InitGamePlayModule();

protected:

	virtual void BeginPlay() override;



public:

	class ADSPlayerController* SPController;

	class ADSPlayerCharacter* SPCharacter;

	class ADSPlayerState* SPState;

	

	
};
