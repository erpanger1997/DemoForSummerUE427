// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSProjectileBase.h"
#include <Common/DSHelper.h>

// Sets default values
ADSProjectileBase::ADSProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADSProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADSProjectileBase::ProjectileInitialize(float Damage)
{

	// DSHelper::Debug(FString::Printf(TEXT("ADSProjectileBase::ProjectileInitialize")), 5);
	BaseDamage = Damage;
}

