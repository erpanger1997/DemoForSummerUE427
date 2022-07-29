// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "DSBulletShell.generated.h"

UCLASS()
class DEMOFORSUMMERUE427_API ADSBulletShell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSBulletShell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroyBulletShell();
protected:

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		UStaticMeshComponent* BulletShellComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovementComponent;

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		float DestroyDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		float MinInitialSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		float MaxInitialSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		FRotator ThrowDirection = FRotator(60.f, 180.f, 0);

};
