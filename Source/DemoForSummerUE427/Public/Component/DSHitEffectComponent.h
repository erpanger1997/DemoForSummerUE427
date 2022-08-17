// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <ParticleSystem/DSImpactParticleSystem.h>
#include "DSHitEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOFORSUMMERUE427_API UDSHitEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDSHitEffectComponent();

	void PlayHitEffect(EPhysicalSurface SurfaceType, FVector HitPoint, FRotator Rotation);

protected:

	virtual void BeginPlay() override;


protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HitEffect)
		TSubclassOf<ADSImpactParticleSystem> DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HitEffect)
		TSubclassOf<ADSImpactParticleSystem> FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HitEffect)
		TSubclassOf<ADSImpactParticleSystem> StoneImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HitEffect)
		TSubclassOf<ADSImpactParticleSystem> WoodImpactEffect;

};
