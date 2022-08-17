// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleSystem/DSImpactParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADSImpactParticleSystem::ADSImpactParticleSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->OnParticleCollide.AddDynamic(this, &ADSImpactParticleSystem::OnParticleCollide);
	RootComponent = ParticleSystemComponent;

	InitialLifeSpan = 3.f;
}

void ADSImpactParticleSystem::OnParticleCollide(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat)
{
	if (DecalMaterial)
	{
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, DecalSize, Location, Normal.Rotation(), 10.f);
	}
}

