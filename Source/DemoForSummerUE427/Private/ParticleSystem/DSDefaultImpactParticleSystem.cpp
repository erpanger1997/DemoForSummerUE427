// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleSystem/DSDefaultImpactParticleSystem.h"
#include <UObject/ConstructorHelpers.h>
#include "Particles/ParticleSystemComponent.h"

ADSDefaultImpactParticleSystem::ADSDefaultImpactParticleSystem()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> defalutImpactParticle(
		TEXT("ParticleSystem'/Game/MilitaryWeapDark/FX/P_Impact_Metal_Small_01.P_Impact_Metal_Small_01'"));

	ParticleSystemComponent->SetTemplate(defalutImpactParticle.Object);
}
