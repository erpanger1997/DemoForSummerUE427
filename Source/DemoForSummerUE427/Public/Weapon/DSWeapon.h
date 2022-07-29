// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Enum/EWeaponMode.h>
#include "DSWeapon.generated.h"

class ADSPlayerCharacter;

UCLASS()
class DEMOFORSUMMERUE427_API ADSWeapon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADSWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool BulletCheck(ADSPlayerCharacter* MyOwner);

	virtual void BulletFire(ADSPlayerCharacter* MyOwner);

	void ShakeCamera();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FName TracerTargetName = "Target";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FName BulletShellName = "BulletShell";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FName ClipBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		EWeaponMode CurrentWeaponMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		UParticleSystem* MuzzleEffect;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		TSubclassOf<AMultiShootGameBulletShell> BulletShellClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		TSubclassOf<AMultiShootGameMagazineClip> MagazineClipClass;*/

	FTimerHandle TimerHandle;

	float LastFireTime;

	float TimeBetweenShots;

	bool Loop = false;

};
