// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSMagazineClip.generated.h"

UCLASS()
class DEMOFORSUMMERUE427_API ADSMagazineClip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADSMagazineClip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ThrowMagazineClip(UStaticMesh* MagazineClipMesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroyMagazineClip();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* MagazineClipMeshComponent;

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		float DestroyDelay = 2.0f;

};
