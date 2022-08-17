// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSWeapon.h"
#include "Components/AudioComponent.h"
#include <Common/DSHelper.h>
#include <Player/DSPlayerCharacter.h>
#include <Kismet/KismetMathLibrary.h>
#include <Weapon/DSProjectileBase.h>
#include <Weapon/DSProjectileBullet.h>
#include <Weapon/DSTempBullet.h>

// Sets default values
ADSWeapon::ADSWeapon()
{
	DSHelper::Debug(FString(TEXT("ADSWeapon::ADSWeapon()")), 10);
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponmeshComponent"));
	WeaponMeshComponent->SetupAttachment(RootComponent);
	WeaponMeshComponent->SetCastHiddenShadow(true);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false);

	SetWeaponInfo();
}

// Called when the game starts or when spawned
void ADSWeapon::BeginPlay()
{
	Super::BeginPlay();


	WeaponMeshComponent->SetSkeletalMesh(WeaponInfo.WeaponMesh);

	TimeBetweenShots = 60.0f / WeaponInfo.RateOfFire;
}

void ADSWeapon::ShakeCamera()
{\
	if (SPCharacter)
	{
		if (SPCharacter->GetWeaponMode() == EWeaponMode::MainWeapon)
		{
			SPCharacter->AddControllerYawInput(FMath::RandRange(-1 * WeaponInfo.CameraSpread, WeaponInfo.CameraSpread));
			SPCharacter->AddControllerPitchInput(
				-1 * FMath::RandRange(-1 * WeaponInfo.CameraSpreadDown, WeaponInfo.CameraSpread));
		}

		APlayerController* PlayerController = Cast<APlayerController>(SPCharacter->GetController());
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(WeaponInfo.FireCameraShake);
		}
	}
}

void ADSWeapon::InitSPCharacter()
{

	if (!SPCharacter) {
		if (!GetOwner()) {

			DSHelper::Debug(FString(TEXT("InitSPCharacter get owner fail")), 1);
		}
		SPCharacter = Cast<ADSPlayerCharacter>(GetOwner());
		// DSHelper::Debug(FString(GetOwner()->GetName()), 1);
	}
}

void ADSWeapon::SetWeaponInfo()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshWeapon(
		TEXT("SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

	static ConstructorHelpers::FObjectFinder<UTexture> WeaponImage(
		TEXT("Texture2D'/Game/FPWeapon/Materials/Colors.Colors'"));

	static ConstructorHelpers::FClassFinder<UMatineeCameraShake> FireCameraShake(
		TEXT("Blueprint'/Game/BluePrints/CameraShake/BP_MainWeaponCameraShake.BP_MainWeaponCameraShake_C'"));

	static ConstructorHelpers::FClassFinder<ADSProjectileBullet> BulletClass(
		TEXT("Blueprint'/Game/BluePrints/Weapon/BP_Bullet.BP_Bullet_C'"));

	FVector AimVector(0.f, -15.f, 14.f);

	WeaponInfo.Name = FString(TEXT("Special Shader"));

	WeaponInfo.WeaponMesh = StaticMeshWeapon.Object;

	WeaponInfo.WeaponImage = WeaponImage.Object;

	WeaponInfo.MagazineClipMesh = nullptr;

	WeaponInfo.FireCameraShake = FireCameraShake.Class;

	WeaponInfo.BaseDamage = 40.f;

	WeaponInfo.RateOfFire = 550.f;

	WeaponInfo.DelayOfShotgun = 0.3;

	WeaponInfo.BulletSpread = 0.5;

	WeaponInfo.CameraSpread = 1.0;

	WeaponInfo.CameraSpreadDown = 0.9;

	WeaponInfo.AimVector = AimVector;

	WeaponInfo.AimTexture = false;

	WeaponInfo.BulletNumber = 30;

	WeaponInfo.FillUpBulletNumber = 30;

	WeaponInfo.MaxBulletNumber = 90;

	WeaponInfo.FillUpMaxBulletNumber = 90;

	WeaponInfo.ProjectileClass = ADSProjectileBullet::StaticClass();
	ProjectileClass = ADSTempBullet::StaticClass();
}

void ADSWeapon::Fire()
{
	
	if (BulletCheck(SPCharacter))
	{
		return;
	}

	if (SPCharacter)
	{
		DSHelper::Debug(FString(TEXT("Fire")), 1);
		FVector EyeLocation;
		FRotator EyeRotation;

		if (SPCharacter->GetAimed())
		{
			EyeLocation = SPCharacter->CurrentFPSCamera->GetCameraComponent()->GetComponentLocation();
			EyeRotation = SPCharacter->CurrentFPSCamera->GetCameraComponent()->GetComponentRotation();
		}
		else
		{
			EyeLocation = SPCharacter->GetCameraComponent()->GetComponentLocation();
			EyeRotation = SPCharacter->GetCameraComponent()->GetComponentRotation();
		}

		FVector ShotDirection = EyeRotation.Vector();

		const float HalfRad = FMath::DegreesToRadians(WeaponInfo.BulletSpread);	// 设置子弹偏移
		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);		// 射击方向

		const FVector TraceEnd = EyeLocation + (ShotDirection * 3000.f);

		if (Cast<ADSFirstWeapon>(this))
		{
			const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EyeLocation, TraceEnd);

			const FRotator TargetRotation = FRotator(0, LookAtRotation.Yaw - 90.f, LookAtRotation.Pitch * -1.f);

			Cast<ADSPlayerCharacter>(GetOwner())->GetFPSCameraSceneComponent()->SetWorldRotation(TargetRotation);
		}

		/*if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMeshComponent, MuzzleSocketName);
		}*/
		//if (ProjectileClass != nullptr)
		//{
		//	UWorld* const World = GetWorld();
		//	if (World != nullptr)
		//	{
		//		const FVector MuzzleLocation = WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
		//		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		//		const FRotator ShotTargetDirection = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TraceEnd);

		//		//Set Spawn Collision Handling Override
		//		FActorSpawnParameters ActorSpawnParams;
		//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		//		// spawn the projectile at the muzzle
		//		World->SpawnActor<ADSTempBullet>(ProjectileClass, MuzzleLocation, ShotTargetDirection, ActorSpawnParams);

		//	}
		//}

		if (WeaponInfo.ProjectileClass)
		{
			const FVector MuzzleLocation = WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
			const FRotator ShotTargetDirection = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TraceEnd);

			ADSProjectileBase* Projectile = GetWorld()->SpawnActor<ADSProjectileBullet>(
				WeaponInfo.ProjectileClass, MuzzleLocation, ShotTargetDirection);

			// DSHelper::Debug(FString::Printf(TEXT("SpawnActor:: ADSProjectileBase")), 5);
			Projectile->SetOwner(GetOwner());
			Projectile->ProjectileInitialize(WeaponInfo.BaseDamage);
		}

		if (SPCharacter->GetWeaponMode() != EWeaponMode::SecondWeapon && BulletShellClass)
		{
			const FVector BulletShellLocation = WeaponMeshComponent->GetSocketLocation(BulletShellName);
			const FRotator BulletShellRotation = WeaponMeshComponent->GetComponentRotation();

			ADSBulletShell* BulletShell = GetWorld()->SpawnActor<ADSBulletShell>(
				BulletShellClass, BulletShellLocation, BulletShellRotation);
			BulletShell->SetOwner(this);
			// BulletShell->ThrowBulletShell();
		}

		ShakeCamera();

		BulletFire(SPCharacter);

		AudioComponent->Play();

		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void ADSWeapon::StartFire()
{
	DSHelper::Debug(FString(TEXT("startFire")), 1);
	InitSPCharacter();
	const float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADSWeapon::Fire, TimeBetweenShots, true,
		FirstDelay);
}

void ADSWeapon::StopFire()
{

	DSHelper::Debug(FString(TEXT("StopFire")), 1);
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ADSWeapon::FireOfDelay()
{
	if (LastFireTime == 0)
	{
		Fire();

		return;
	}

	const float CurrentFireTime = GetWorld()->GetTimeSeconds();

	if (CurrentFireTime - LastFireTime > WeaponInfo.DelayOfShotgun)
	{
		Fire();
	}
}

void ADSWeapon::EnablePhysicsSimulate()
{
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	WeaponMeshComponent->SetCollisionProfileName("BlockAll");
	WeaponMeshComponent->SetSimulatePhysics(true);
}

void ADSWeapon::ReloadShowMagazineClip(bool Enabled)
{
	/*if (Enabled)
	{
		WeaponMeshComponent->UnHideBoneByName(ClipBoneName);
	}
	else
	{
		WeaponMeshComponent->HideBoneByName(ClipBoneName, PBO_None);
		if (WeaponInfo.MagazineClipMesh)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ADSMagazineClip* CurrentMagazineClip = GetWorld()->SpawnActor<ADSMagazineClip>(
				MagazineClipClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
			CurrentMagazineClip->SetOwner(this);
			CurrentMagazineClip->AttachToComponent(WeaponMeshComponent,
				FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Magazine"));

			CurrentMagazineClip->ThrowMagazineClip(WeaponInfo.MagazineClipMesh);
		}
	}*/
}

bool ADSWeapon::BulletCheck(ADSPlayerCharacter* MyOwner)
{
	if (WeaponInfo.BulletNumber == 0 && WeaponInfo.MaxBulletNumber == 0)
	{
		return true;
	}

	return false;
}

void ADSWeapon::BulletFire(ADSPlayerCharacter* MyOwner)
{
	if (WeaponInfo.BulletNumber > 0)
	{
		WeaponInfo.BulletNumber--;
		DSHelper::Debug(FString::Printf(TEXT("num of bullet number = %d"), WeaponInfo.BulletNumber), 1.f);
	}
	else
	{
		MyOwner->BeginReload();
	}
}

void ADSWeapon::BulletReload()
{
	if (WeaponInfo.MaxBulletNumber > WeaponInfo.FillUpBulletNumber)
	{
		if (WeaponInfo.BulletNumber < WeaponInfo.FillUpBulletNumber)
		{
			const int TempNumber = WeaponInfo.FillUpBulletNumber - WeaponInfo.BulletNumber;
			WeaponInfo.BulletNumber = WeaponInfo.FillUpBulletNumber;
			WeaponInfo.MaxBulletNumber -= TempNumber;
		}
		else
		{
			WeaponInfo.BulletNumber += WeaponInfo.FillUpBulletNumber;
			WeaponInfo.MaxBulletNumber -= WeaponInfo.FillUpBulletNumber;
		}
	}
	else
	{
		if (WeaponInfo.BulletNumber + WeaponInfo.MaxBulletNumber > WeaponInfo.FillUpBulletNumber)
		{
			const int TempNumber = WeaponInfo.FillUpBulletNumber - WeaponInfo.BulletNumber;
			WeaponInfo.BulletNumber = WeaponInfo.FillUpBulletNumber;
			WeaponInfo.MaxBulletNumber -= TempNumber;;
		}
		else
		{
			WeaponInfo.BulletNumber += WeaponInfo.MaxBulletNumber;
			WeaponInfo.MaxBulletNumber = 0;
		}
	}
}

void ADSWeapon::FillUpBullet()
{
	WeaponInfo.BulletNumber = WeaponInfo.FillUpBulletNumber;
	WeaponInfo.MaxBulletNumber = WeaponInfo.FillUpMaxBulletNumber;
}

USkeletalMeshComponent* ADSWeapon::GetWeaponMeshComponent() const
{

	return WeaponMeshComponent;
}

UAudioComponent* ADSWeapon::GetAudioComponent() const
{
	return AudioComponent;
}
