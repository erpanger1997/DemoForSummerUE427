// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSMagazineClip.h"

// Sets default values
ADSMagazineClip::ADSMagazineClip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSMagazineClip::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADSMagazineClip::DestroyMagazineClip()
{

}

// Called every frame
void ADSMagazineClip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADSMagazineClip::ThrowMagazineClip(UStaticMesh* MagazineClipMesh)
{

}

