// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/DSProjectileBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Component/DSHitEffectComponent.h>
#include "DSProjectileBullet.generated.h"

/**
 * 
 */
UCLASS()
class DEMOFORSUMMERUE427_API ADSProjectileBullet : public ADSProjectileBase
{
	GENERATED_BODY()

public:
	ADSProjectileBullet();

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		UDSHitEffectComponent* HitEffectComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		UMaterialInterface* BulletDecalMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		FVector BulletDecalSize;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverLappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

};
