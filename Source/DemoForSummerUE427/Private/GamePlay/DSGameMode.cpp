// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/DSGameMode.h"
#include "UI/HUD/DSGameHUD.h"
#include <Player/DSPlayerController.h>
#include <Player/DSPlayerState.h>
#include <Player/DSPlayerCharacter.h>
#include "Kismet/GameplayStatics.h"

ADSGameMode::ADSGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	HUDClass = ADSGameHUD::StaticClass();
	PlayerControllerClass = ADSPlayerController::StaticClass();
	PlayerStateClass = ADSPlayerState::StaticClass();
	DefaultPawnClass = ADSPlayerCharacter::StaticClass();
}

void ADSGameMode::Tick(float DeltaSeconds)
{
	
}

void ADSGameMode::InitGamePlayModule()
{
	SPController = Cast<ADSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	SPCharacter = Cast<ADSPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SPState = Cast<ADSPlayerState>(SPController->PlayerState);
}

void ADSGameMode::BeginPlay()
{
	if (!SPController) {
		InitGamePlayModule();
	}
}
