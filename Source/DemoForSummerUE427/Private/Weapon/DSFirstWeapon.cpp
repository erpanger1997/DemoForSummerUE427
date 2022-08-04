// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSFirstWeapon.h"
#include "Components/AudioComponent.h"
#include <Player/DSPlayerCharacter.h>
#include "Weapon/DSWeapon.h"
#include <Common/DSHelper.h>
#include <GameFramework/SpringArmComponent.h>

ADSFirstWeapon::ADSFirstWeapon()
{

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(WeaponMeshComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 20.f;
	SpringArmComponent->SocketOffset = FVector(0.f, 90.f, 80.f);
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 10.f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ADSFirstWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TargetFOV = WeaponInfo.AimTexture ? ZoomedFOV : DefaultFOV;
	const float CurrentFOV = FMath::FInterpTo(CameraComponent->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	CameraComponent->SetFieldOfView(CurrentFOV);
}

bool ADSFirstWeapon::BulletCheck(ADSPlayerCharacter* MyOwner)
{
	switch (MyOwner->GetWeaponMode())
	{
	case EWeaponMode::MainWeapon:
		if (MyOwner->CurrentMainWeapon->WeaponInfo.BulletNumber == 0 &&
			MyOwner->CurrentMainWeapon->WeaponInfo.MaxBulletNumber == 0)
		{
			return true;
		}
	/*case EWeaponMode::SecondWeapon:
		if (MyOwner->CurrentSecondWeapon->WeaponInfo.BulletNumber == 0 &&
			MyOwner->CurrentSecondWeapon->WeaponInfo.MaxBulletNumber == 0)
		{
			return true;
		}
	case EWeaponMode::ThirdWeapon:
		if (MyOwner->CurrentThirdWeapon->WeaponInfo.BulletNumber == 0 &&
			MyOwner->CurrentThirdWeapon->WeaponInfo.MaxBulletNumber == 0)
		{
			return true;
		}*/
	}
	return false;
}

void ADSFirstWeapon::BulletFire(ADSPlayerCharacter* MyOwner)
{
	if (!MyOwner) {

		DSHelper::Debug(FString::Printf(TEXT("BeginPlay get BulletFire fali")), 5);
	}
	switch (MyOwner->GetWeaponMode())
	{
	case EWeaponMode::MainWeapon:
		if (MyOwner->CurrentMainWeapon->WeaponInfo.BulletNumber > 0)
		{
			MyOwner->CurrentMainWeapon->WeaponInfo.BulletNumber--;
			DSHelper::Debug(FString::Printf(TEXT("num of bullet number = %d"), MyOwner->CurrentMainWeapon->WeaponInfo.BulletNumber), 1.f);
		}
		else
		{
			MyOwner->BeginReload();
		}
		break;
	/*case EWeaponMode::SecondWeapon:
		if (MyOwner->CurrentSecondWeapon->WeaponInfo.BulletNumber > 0)
		{
			MyOwner->CurrentSecondWeapon->WeaponInfo.BulletNumber--;
		}
		else
		{
			MyOwner->BeginReload();
		}
		break;
	case EWeaponMode::ThirdWeapon:
		if (MyOwner->CurrentThirdWeapon->WeaponInfo.BulletNumber > 0)
		{
			MyOwner->CurrentThirdWeapon->WeaponInfo.BulletNumber--;
		}
		else
		{
			MyOwner->BeginReload();
		}*/
	}
}

UCameraComponent* ADSFirstWeapon::GetCameraComponent() const
{
	return CameraComponent;
}

void ADSFirstWeapon::SetWeaponInfo(const ADSWeapon* Weapon)
{
	WeaponInfo = Weapon->WeaponInfo;
	WeaponMeshComponent->SetSkeletalMesh(!Weapon->WeaponInfo.AimTexture
		? Weapon->GetWeaponMeshComponent()->SkeletalMesh
		: nullptr);

	CameraComponent->SetRelativeTransform(FTransform(FQuat(FRotator(0, 90.f, 0)),
		Weapon->WeaponInfo.AimVector,
		FVector::OneVector));
	AudioComponent->Stop();
	AudioComponent->SetSound(Weapon->GetAudioComponent()->Sound);
}

void ADSFirstWeapon::BeginPlay()
{
	Super::BeginPlay();

	DefaultFOV = CameraComponent->FieldOfView;
}
