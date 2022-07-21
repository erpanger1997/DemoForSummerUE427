// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DSPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class DEMOFORSUMMERUE427_API UDSPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	UDSPlayerAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	void InitSPCharacter();

	void UpdateParameter();

	void UpdateMontage();

	void AllowViewChange(bool IsAllow);

	void UpdateJumpFallData();

	void UpdateGroundDistance();

	FHitResult RayGetHitResult(FVector TraceStart, FVector TraceEnd);

	void RunRayCast();

	void UpdateLocationData(float DeltaSeconds);


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool HasVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FRotator SpineRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float TimeToJumpApex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float GroundDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FVector WorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float DisplacementSinceLastUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float DisplacementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsFirstUpdate;

protected:

	class ADSPlayerCharacter* SPCharacter;
};
