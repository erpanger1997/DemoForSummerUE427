// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
UENUM(BlueprintType)
enum class EWeaponMode : uint8
{
	MainWeapon UMETA(DisplayName = "MainWeapon"),
	SecondWeapon UMETA(DisplayName = "SecondWeapon"),
	ThirdWeapon UMETA(DisplayName = "ThirdWeapon")
};