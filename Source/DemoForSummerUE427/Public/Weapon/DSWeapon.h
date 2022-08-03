// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Enum/EWeaponMode.h>
#include <Struct/WeaponInfo.h>
#include "DSBulletShell.h"
#include "DSMagazineClip.h"
#include "DSWeapon.generated.h"

class ADSPlayerCharacter;

UCLASS()
class DEMOFORSUMMERUE427_API ADSWeapon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADSWeapon();

	void Fire();

	void StartFire();

	void StopFire();

	void FireOfDelay();

	void EnablePhysicsSimulate();

	void ReloadShowMagazineClip(bool Enabled);

	void BulletReload();

	void FillUpBullet();

	USkeletalMeshComponent* GetWeaponMeshComponent() const;

	UAudioComponent* GetAudioComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool BulletCheck(ADSPlayerCharacter* MyOwner);

	void BulletFire(ADSPlayerCharacter* MyOwner);

	void ShakeCamera();

	void InitSPCharacter();

private:

	void SetWeaponInfo();

public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		FWeaponInfo WeaponInfo;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		TSubclassOf<ADSBulletShell> BulletShellClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
		TSubclassOf<ADSMagazineClip> MagazineClipClass;

	FTimerHandle TimerHandle;

	float LastFireTime;

	float TimeBetweenShots;

	bool Loop = false;


	class ADSPlayerCharacter* SPCharacter;
};
