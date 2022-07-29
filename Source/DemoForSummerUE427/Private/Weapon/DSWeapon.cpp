// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSWeapon.h"

// Sets default values
ADSWeapon::ADSWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ADSWeapon::BulletCheck(ADSPlayerCharacter* MyOwner)
{
	return false;
}

void ADSWeapon::BulletFire(ADSPlayerCharacter* MyOwner)
{

}

void ADSWeapon::ShakeCamera()
{

}

// Called every frame
void ADSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
