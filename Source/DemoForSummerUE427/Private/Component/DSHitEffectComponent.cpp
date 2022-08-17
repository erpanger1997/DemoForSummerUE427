// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DSHitEffectComponent.h"
#include <../DemoForSummerUE427.h>
#include <ParticleSystem/DSDefaultImpactParticleSystem.h>

// Sets default values for this component's properties
UDSHitEffectComponent::UDSHitEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}



void UDSHitEffectComponent::PlayHitEffect(EPhysicalSurface SurfaceType, FVector HitPoint, FRotator Rotation)
{
	TSubclassOf<ADSImpactParticleSystem> SelectEffect = nullptr;

	switch (SurfaceType)
	{
	case SURFACE_CHARACTER:
	case SURFACE_HEAD:
		SelectEffect = FleshImpactEffect;
		break;
	case SURFACE_STONE:
		SelectEffect = StoneImpactEffect;
		break;
	case SURFACE_WOOD:
		SelectEffect = WoodImpactEffect;
		break;
	default:
		SelectEffect = DefaultImpactEffect;
		break;
	}

	GetWorld()->SpawnActor<AActor>(SelectEffect, HitPoint, Rotation);
}

void UDSHitEffectComponent::BeginPlay()
{
	DefaultImpactEffect = ADSDefaultImpactParticleSystem::StaticClass();
	FleshImpactEffect = ADSDefaultImpactParticleSystem::StaticClass();
	StoneImpactEffect = ADSDefaultImpactParticleSystem::StaticClass();
	WoodImpactEffect = ADSDefaultImpactParticleSystem::StaticClass();
}

