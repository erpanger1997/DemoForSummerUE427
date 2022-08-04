// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/DSWeapon.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include "DSFirstWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DEMOFORSUMMERUE427_API ADSFirstWeapon : public ADSWeapon
{
	GENERATED_BODY()
	

public:
	// Sets default values for this pawn's properties
	ADSFirstWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool BulletCheck(ADSPlayerCharacter* MyOwner) override;

	virtual void BulletFire(ADSPlayerCharacter* MyOwner) override;

	UCameraComponent* GetCameraComponent() const;

	void SetWeaponInfo(const ADSWeapon* Weapon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		float ZoomedFOV = 60.0f;

	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (ClampMin = 0.1f, ClampMax = 100.0f))
		float ZoomInterpSpeed = 20.0f;;

public:
};
