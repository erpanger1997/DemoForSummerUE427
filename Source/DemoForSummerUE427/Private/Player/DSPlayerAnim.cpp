// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DSPlayerAnim.h"
#include <Player/DSPlayerCharacter.h>
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Common/DSHelper.h>
#include "Engine/World.h"
#include <CollisionQueryParams.h>
#include <GameFramework/Character.h>
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>


UDSPlayerAnim::UDSPlayerAnim()
{
	Speed = 0.f;
	Direction = 0.f;
	AimYaw = 0.f;
	HalfHeight = 0.f;
	HasVelocity = false;
	isCrouching = false;

	SpineRotator = FRotator(0.f, 0.f, 0.f);

	IsInAir = false;
	IsOnGround = true;
	IsJumping = false;
	IsFalling = false;
	// TimeToJumpApex = 0.f;
	/*IsFirstUpdate = true;
	DisplacementSinceLastUpdate = 0.f;
	DisplacementSpeed = 0.f;*/
}

void UDSPlayerAnim::NativeInitializeAnimation()
{	
	Super::NativeInitializeAnimation();
	InitSPCharacter();
	if (!SPCharacter->GetCapsuleComponent()) {

		return;
	}
	//
	// HalfHeight = SPCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

void UDSPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ATrap::SteppedToTrigger_Implementation -- AddOnScreenDebugMessage!!!!");
	// InitSPCharacter();

	UpdateParameter();

	UpdateMontage();

	// UpdateAimYaw(DeltaSeconds);

	UpdateLocationData(DeltaSeconds);
}

void UDSPlayerAnim::InitSPCharacter()
{

	if (!SPCharacter) {
		SPCharacter = Cast<ADSPlayerCharacter>(TryGetPawnOwner());
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("-- speed = ,%d"), SPCharacter ? 1 : 0));
}

void UDSPlayerAnim::UpdateParameter()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("-- speed = ,%d"), SPCharacter ? 1: 0));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("-- speed = ,%f"), Speed));
	if (!SPCharacter) {
		return;
	}

	HalfHeight = SPCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	Speed = SPCharacter->GetVelocity().Size();
	Direction = CalculateDirection(SPCharacter->GetVelocity(), SPCharacter->K2_GetActorRotation());
	HasVelocity = Speed > 0 ? true : false;
	isCrouching = SPCharacter->GetMovementComponent()->IsCrouching();
	IsFalling = SPCharacter->GetMovementComponent()->IsFalling();

	float SpineDir = SPCharacter->GetActorRotation().Yaw - 90.f;
	if (SpineDir > 180.f) {
		SpineDir -= 360.f;
	}
	if (SpineDir < -180.f) {
		SpineDir += 360.f;
	}
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
	// UpdateJumpFallData();
	UpdateGroundDistance();
	DSHelper::Debug(FString::Printf(TEXT("-- speed = %f"), Speed), 0.1);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("-- speed = %f"), Speed));
}

void UDSPlayerAnim::UpdateAimYaw(float DeltaSeconds)
{
	FRotator DeltaRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation() - SPCharacter->K2_GetActorRotation();
	DeltaRotation.Normalize();
	FRotator CurrentRotation = UKismetMathLibrary::MakeRotator(0, 0, AimYaw);
	AimYaw = UKismetMathLibrary::ClampAngle(UKismetMathLibrary::RInterpTo(CurrentRotation, DeltaRotation, DeltaSeconds, 15.0).Yaw, -90.f, 90.f);
}

void UDSPlayerAnim::UpdateMontage()
{

}

void UDSPlayerAnim::AllowViewChange(bool IsAllow)
{

}

void UDSPlayerAnim::UpdateJumpFallData()
{
	/*IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	IsOnGround = SPCharacter->GetCharacterMovement()->IsMovingOnGround();
	IsJumping = false;
	IsJumping = false;
	if (SPCharacter->GetCharacterMovement()->IsFalling()) {
		if (SPCharacter->GetVelocity().Z > 0.f) {
			IsJumping = true;
		}
		else IsFalling = true;
	}*/
	//IsJumping = SPCharacter->GetCharacterMovement()->IsFalling() && SPCharacter->GetVelocity().Z > 0.f;
	//IsFalling = !IsJumping;
	/*if (IsJumping) TimeToJumpApex = 0.f;
	else {
		float GravityZ = SPCharacter->GetCharacterMovement()->GetGravityZ();
		TimeToJumpApex = (0 - SPCharacter->GetVelocity().Z) / GravityZ;
	}*/
	//DSHelper::Debug(FString::Printf(TEXT("-- TimeToJumpApex = %f"), TimeToJumpApex), 0.1);
}

void UDSPlayerAnim::UpdateGroundDistance()
{
	if (IsFalling) {
		// 如果正在下落，则打一条指向地面的射线获取到达地面的距离
		RunRayCast();
	}
}

FHitResult UDSPlayerAnim::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	// 定义射线检测的参数
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(SPCharacter);
	TraceParams->bTraceComplex = true;
	// 返回值中是否包含物理材质
	TraceParams->bReturnPhysicalMaterial = false;
	// 检测混合的碰撞
	TraceParams->bTraceComplex = true;

	FHitResult Hit(ForceInit);
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, *TraceParams)) {
		// 绘制射线5秒
	}
	return Hit;
}

void UDSPlayerAnim::RunRayCast()
{
	FVector StartPos(0.f);
	FVector EndPos(0.f);
	StartPos = SPCharacter->GetActorLocation();
	EndPos = SPCharacter->GetActorLocation();
	EndPos.Z -= 10000.f - SPCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	bool IsDetect = false;
	FHitResult Hit = RayGetHitResult(StartPos, EndPos);
	GroundDistance = Hit.Distance;
	DSHelper::Debug(FString::Printf(TEXT("-- GroundDistance = %f"), GroundDistance), 0.1);
}

void UDSPlayerAnim::UpdateLocationData(float DeltaSeconds)
{
	if (!SPCharacter) {
		return;
	}
	FVector DeltaDistance(0.f);
	DeltaDistance = SPCharacter->GetActorLocation() - WorldLocation;
	WorldLocation = SPCharacter->GetActorLocation();

	/*DisplacementSinceLastUpdate = sqrt(FMath::Square(DeltaDistance.X) + FMath::Square(DeltaDistance.Y));

	DisplacementSpeed = DisplacementSinceLastUpdate / DeltaSeconds;
	if (IsFirstUpdate) {
		DisplacementSinceLastUpdate = 0.f;
		DisplacementSpeed = 0.f;
		IsFirstUpdate = false;
	}
	DSHelper::Debug(FString::Printf(TEXT("-- DisplacementSpeed = %f"), DisplacementSpeed), 0.1);*/
}
