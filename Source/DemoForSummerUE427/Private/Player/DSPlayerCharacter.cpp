// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DSPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include <GameFramework/Pawn.h>
#include <Math/RotationMatrix.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Runtime/Engine/Classes/Components/ChildActorComponent.h"
#include "UObject/ConstructorHelpers.h"
//#include "Microsoft/COMPointer.h"
#include "Chaos/Rotation.h"
//#include "IOS/IOSSystemIncludes.h"
#include <Engine/EngineTypes.h>
#include <Components/InputComponent.h>
#include <Player/DSPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>
#include <Components/PrimitiveComponent.h>
#include <Components/AudioComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <PhysicalMaterials/PhysicalMaterial.h>
//#include <Hand/DSHandObject.h>

// Sets default values
ADSPlayerCharacter::ADSPlayerCharacter()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(
		TEXT("SkeletalMesh'/Game/Character/Swat/swat.swat'"));
	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false; // 是否允许贴花
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(
	//	TEXT("AnimBlueprint'/Game/BluePrints/Animation/ABP_DSPlayerCharacter.ABP_DSPlayerCharacter_C'"));
	//GetMesh()->AnimClass = StaticAnimThird.Class;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->SocketOffset = FVector(0.f, 90.f, 80.f);
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 0.f);



	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	CameraComponent->SetActive(true);


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bNotifyApex = true;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	BaseLookUpRate = 45.f;
	BaseTurnRate = 45.f;

	/*MainWeaponSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MainWeaponSceneComponent"));
	MainWeaponSceneComponent->SetupAttachment(GetMesh(), MainWeaponSocketName);

	SecondWeaponSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SecondWeaponSceneComponent"));
	SecondWeaponSceneComponent->SetupAttachment(GetMesh(), BackSecondWeaponSocketName);

	ThirdWeaponSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdWeaponSceneComponent"));
	ThirdWeaponSceneComponent->SetupAttachment(GetMesh(), BackThirdWeaponSocketName);

	GrenadeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("GrenadeSceneComponent"));
	GrenadeSceneComponent->SetupAttachment(GetMesh(), GrenadeSocketName);

	KnifeSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("KnifeSkeletalMeshComponent"));
	KnifeSkeletalMeshComponent->SetupAttachment(GetMesh(), KnifeSocketName);
	KnifeSkeletalMeshComponent->SetVisibility(false);*/

	/*FPSCameraSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FPSCameraSceneComponent"));
	FPSCameraSceneComponent->SetupAttachment(RootComponent);

	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathAudioComponent"));
	DeathAudioComponent->SetupAttachment(RootComponent);
	DeathAudioComponent->SetAutoActivate(false);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	HitEffectComponent = CreateDefaultSubobject<UHitEffectComponent>(TEXT("HitEfectComponent"));*/

}


void ADSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 实例化控制器指针
	//SPController = Cast<ADSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// 吧手持物品组件绑定到右手插槽
	// HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandRSlot"));

	// 添加actor
	// HandObject->SetChildActorClass(ADSHandObject::SpawnHandObject(1));

	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	PlayerCameraManager->ViewPitchMax = CameraPitchClamp;
	PlayerCameraManager->ViewPitchMin = -1 * CameraPitchClamp;

	GrenadeCount = MaxGrenadeCount; // 设置手雷数量

	// 开始不显示狙击镜下的widget
	CurrentSniperUserWidget = CreateWidget(GetWorld(), SniperUserWidgetClass);
	CurrentSniperUserWidget->AddToViewport();
	CurrentSniperUserWidget->SetVisibility(ESlateVisibility::Hidden);

	CurrentGameUserWidget = CreateWidget(GetWorld(), GameUserWidgetClass);
	CurrentGameUserWidget->AddToViewport();

	// HealthComponent->OnHealthChanged.AddDynamic(this, &AMultiShootGameCharacter::OnHealthChanged);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 设置component

	/*CurrentMainWeapon = GetWorld()->SpawnActor<AMultiShootGameWeapon>(MainWeaponClass, FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParameters);
	CurrentSecondWeapon = GetWorld()->SpawnActor<AMultiShootGameWeapon>(SecondWeaponClass, FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParameters);
	CurrentThirdWeapon = GetWorld()->SpawnActor<AMultiShootGameWeapon>(ThirdWeaponClass, FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParameters);
	CurrentFPSCamera = GetWorld()->SpawnActor<AMultiShootGameFPSCamera>(FPSCameraClass, FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParameters);*/

	/*if (CurrentMainWeapon)
	{
		CurrentMainWeapon->SetOwner(this);
		CurrentMainWeapon->AttachToComponent(MainWeaponSceneComponent,
			FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	if (CurrentSecondWeapon)
	{
		CurrentSecondWeapon->SetOwner(this);
		CurrentSecondWeapon->AttachToComponent(SecondWeaponSceneComponent,
			FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	if (CurrentThirdWeapon)
	{
		CurrentThirdWeapon->SetOwner(this);
		CurrentThirdWeapon->AttachToComponent(ThirdWeaponSceneComponent,
			FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	if (CurrentFPSCamera)
	{
		CurrentFPSCamera->SetOwner(this);
		CurrentFPSCamera->AttachToComponent(FPSCameraSceneComponent,
			FAttachmentTransformRules::SnapToTargetIncludingScale);

		CurrentFPSCamera->SetActorHiddenInGame(true);

		CurrentFPSCamera->SetWeaponInfo(CurrentMainWeapon);
	}

	if (CurrentGrenade)
	{
		CurrentGrenade->SetOwner(this);
		CurrentGrenade->AttachToComponent(GrenadeSceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}*/
}


void ADSPlayerCharacter::StartFire()
{
	if (!CheckStatus(false, true))
	{
		return;
	}

	bFired = true;


	ToggleUseControlRotation(true);

	if (!bAimed)
	{
		/*switch (WeaponMode)
		{
		case EWeaponMode::MainWeapon:
			if (CurrentMainWeapon)
			{
				CurrentMainWeapon->StartFire();
			}
			break;
		case EWeaponMode::SecondWeapon:
			if (CurrentSecondWeapon)
			{
				CurrentSecondWeapon->Fire();
				BeginSecondWeaponReload();
			}
			break;
		case EWeaponMode::ThirdWeapon:
			if (CurrentThirdWeapon)
			{
				CurrentThirdWeapon->FireOfDelay();
			}
			break;
		}*/
	}
	else
	{
		/*if (CurrentFPSCamera)
		{
			switch (WeaponMode)
			{
			case EWeaponMode::MainWeapon:
				CurrentFPSCamera->StartFire();
				break;
			case EWeaponMode::SecondWeapon:
				CurrentFPSCamera->Fire();
				BeginSecondWeaponReload();
				break;
			case EWeaponMode::ThirdWeapon:
				CurrentFPSCamera->FireOfDelay();
				break;
			}
		}*/
	}
}

void ADSPlayerCharacter::StopFire()
{
	bFired = false;

	ToggleUseControlRotation(false);

	/*if (WeaponMode == EWeaponMode::MainWeapon)
	{
		if (CurrentMainWeapon)
		{
			CurrentMainWeapon->StopFire();
		}

		if (CurrentFPSCamera)
		{
			CurrentFPSCamera->StopFire();
		}
	}*/
}

void ADSPlayerCharacter::MoveForward(float Value)
{

	/*if (Value != 0.f && Controller) {
		const FRotator ControlRot = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::X);


		AddMovementInput(Direction, Value);
	}*/
	if (!bEnableMovement)
	{
		return;
	}

	AddMovementInput(GetActorForwardVector() * Value);

	if (Value != 0)
	{
		if (bAimed)
		{
			// UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStartCameraShake(MovementCameraShakeClass);
		}
	}

}

void ADSPlayerCharacter::MoveRight(float Value)
{
	/*if (Value != 0.f) {
		const FRotator ControlRot = GetControlRotation();
		FVector Direction = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, Value);

	}*/
	/*FRotator ControlRot = GetControlRotation();
	FVector Direction = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);*/

	// AddMovementInput(Direction, Value);
	if (!bEnableMovement)
	{
		return;
	}

	AddMovementInput(GetActorRightVector() * Value);

	if (bAimed && Value != 0)
	{
		// UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStartCameraShake(MovementCameraShakeClass);
	}
}

void ADSPlayerCharacter::BeginFastRun()
{

	bFastRun = true;

	HandleWalkSpeed();
}

void ADSPlayerCharacter::EndFastRun()
{
	bFastRun = false;

	HandleWalkSpeed();
}

void ADSPlayerCharacter::BeginCrouch()
{
	Crouch();

	ToggleUseControlRotation(true);

	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStopCameraShake(FPSCameraShakeClass);
}

void ADSPlayerCharacter::EndCrouch()
{
	UnCrouch();

	ToggleUseControlRotation(false);

	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStartCameraShake(FPSCameraShakeClass);
}

void ADSPlayerCharacter::ToggleCrouch()
{
	if (!GetCharacterMovement()->IsCrouching())
	{
		BeginCrouch();
	}
	else
	{
		EndCrouch();
	}
}

void ADSPlayerCharacter::BeginAim()
{
	if (!CheckStatus(false, true))
	{
		return;
	}

	bAimed = true;

	ToggleUseControlRotation(true);

	SpringArmComponent->SocketOffset = FVector::ZeroVector;

	/*APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetViewTargetWithBlend(CurrentFPSCamera, 0.1f);

	CurrentFPSCamera->SetActorHiddenInGame(false);
	CurrentMainWeapon->SetActorHiddenInGame(true);
	CurrentSecondWeapon->SetActorHiddenInGame(true);
	CurrentThirdWeapon->SetActorHiddenInGame(true);*/
	GetMesh()->SetHiddenInGame(true);

	if (!GetCharacterMovement()->IsCrouching())
	{
		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStartCameraShake(FPSCameraShakeClass);
	}

	/*if (WeaponMode == EWeaponMode::SecondWeapon && CurrentSecondWeapon->WeaponInfo.AimTexture)
	{
		CurrentSniperUserWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (WeaponMode == EWeaponMode::MainWeapon && bFired)
	{
		CurrentFPSCamera->StartFire();
	}

	CurrentMainWeapon->StopFire();*/
}

void ADSPlayerCharacter::EndAim()
{
	bAimed = false;

	ToggleUseControlRotation(false);

	SpringArmComponent->SocketOffset = FVector(0, 90.f, 80.f);
	SpringArmComponent->TargetOffset = FVector(0.f, 0.f, 0.f);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetViewTargetWithBlend(this, 0.1f);

	//CurrentFPSCamera->SetActorHiddenInGame(true);
	//CurrentMainWeapon->SetActorHiddenInGame(false);
	//CurrentSecondWeapon->SetActorHiddenInGame(false);
	//CurrentThirdWeapon->SetActorHiddenInGame(false);
	GetMesh()->SetHiddenInGame(false);

	if (!GetCharacterMovement()->IsCrouching())
	{
		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStopCameraShake(FPSCameraShakeClass);
	}

	/*if (CurrentSecondWeapon->WeaponInfo.AimTexture)
	{
		CurrentSniperUserWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (WeaponMode == EWeaponMode::MainWeapon && bFired)
	{
		CurrentMainWeapon->StartFire();
	}

	CurrentFPSCamera->StopFire();*/
}

void ADSPlayerCharacter::BeginReload()
{
	if (!CheckStatus(false, true))
	{
		return;
	}

	bReloading = true;

	ToggleUseControlRotation(true);

	EndAction();

	/*switch (WeaponMode)
	{
	case EWeaponMode::MainWeapon:
		if (CurrentMainWeapon->WeaponInfo.MaxBulletNumber > 0)
		{
			PlayAnimMontage(ReloadAnimMontage);
		}
	case EWeaponMode::SecondWeapon:
		if (CurrentSecondWeapon->WeaponInfo.MaxBulletNumber > 0)
		{
			PlayAnimMontage(ReloadAnimMontage);
		}
		break;
	case EWeaponMode::ThirdWeapon:
		if (CurrentThirdWeapon->WeaponInfo.MaxBulletNumber > 0)
		{
			PlayAnimMontage(ThirdWeaponReloadAnimMontage);
		}
		break;
	}*/
}


void ADSPlayerCharacter::BeginSecondWeaponReload()
{
	if (!CheckStatus(false, true))
	{
		return;
	}

	bSecondWeaponReloading = true;

	EndAction();

	const FLatentActionInfo LatentActionInfo;
	UKismetSystemLibrary::Delay(GetWorld(), 0.5f, LatentActionInfo);

	PlayAnimMontage(SecondWeaponReloadAnimMontage);
}

void ADSPlayerCharacter::EndReload()
{
	bReloading = false;

	if (!bSecondWeaponReloading)
	{
		/*switch (WeaponMode)
		{
		case EWeaponMode::MainWeapon:
			if (CurrentMainWeapon->WeaponInfo.BulletNumber < CurrentMainWeapon->WeaponInfo.FillUpBulletNumber)
			{
				CurrentMainWeapon->BulletReload();
			}
			break;
		case EWeaponMode::SecondWeapon:
			if (CurrentSecondWeapon->WeaponInfo.BulletNumber < CurrentSecondWeapon->WeaponInfo.FillUpBulletNumber)
			{
				CurrentSecondWeapon->BulletReload();
			}
			break;
		case EWeaponMode::ThirdWeapon:
			if (CurrentThirdWeapon->WeaponInfo.BulletNumber < CurrentThirdWeapon->WeaponInfo.FillUpBulletNumber)
			{
				CurrentThirdWeapon->BulletReload();
			}
			break;
		}*/
	}

	bSecondWeaponReloading = false;

	ToggleUseControlRotation(false);
}

void ADSPlayerCharacter::ReloadShowClip(bool Enabled)
{
	/*AMultiShootGameWeapon* TempWeapon = nullptr;
	switch (WeaponMode)
	{
	case EWeaponMode::MainWeapon:
		TempWeapon = CurrentMainWeapon;
		break;
	case EWeaponMode::SecondWeapon:
		TempWeapon = CurrentSecondWeapon;
		break;
	case EWeaponMode::ThirdWeapon:
		TempWeapon = CurrentThirdWeapon;
		break;
	}

	TempWeapon->ReloadShowMagazineClip(Enabled);*/
}

void ADSPlayerCharacter::ToggleMainWeapon()
{
	if (!CheckStatus(true, true))
	{
		return;
	}

	/*if (WeaponMode == EWeaponMode::MainWeapon)
	{
		return;
	}*/

	bToggleWeapon = true;

	EndAction();

	//WeaponMode = EWeaponMode::MainWeapon;

	//CurrentFPSCamera->SetWeaponInfo(CurrentMainWeapon);

	bUseControllerRotationYaw = false;

	HandleWalkSpeed();

	PlayAnimMontage(WeaponOutAnimMontage);
}

void ADSPlayerCharacter::ToggleSecondWeapon()
{
	if (!CheckStatus(true, true))
	{
		return;
	}

	/*if (WeaponMode == EWeaponMode::SecondWeapon)
	{
		return;
	}*/

	bToggleWeapon = true;

	EndAction();

	/*WeaponMode = EWeaponMode::SecondWeapon;

	CurrentFPSCamera->SetWeaponInfo(CurrentSecondWeapon);*/

	bUseControllerRotationYaw = true;

	HandleWalkSpeed();

	PlayAnimMontage(WeaponOutAnimMontage);
}

void ADSPlayerCharacter::ToggleThirdWeapon()
{
	if (!CheckStatus(true, true))
	{
		return;
	}

	/*if (WeaponMode == EWeaponMode::ThirdWeapon)
	{
		return;
	}*/

	bToggleWeapon = true;

	EndAction();

	//WeaponMode = EWeaponMode::ThirdWeapon;

	//CurrentFPSCamera->SetWeaponInfo(CurrentThirdWeapon);

	bUseControllerRotationYaw = true;

	HandleWalkSpeed();

	PlayAnimMontage(WeaponOutAnimMontage);
}

void ADSPlayerCharacter::ToggleWeaponUp()
{
	/*switch (WeaponMode)
	{
	case EWeaponMode::MainWeapon:
		ToggleThirdWeapon();
		break;
	case EWeaponMode::SecondWeapon:
		ToggleMainWeapon();
		break;
	case EWeaponMode::ThirdWeapon:
		ToggleSecondWeapon();
		break;
	}*/
}

void ADSPlayerCharacter::ToggleWeaponDown()
{
	/*switch (WeaponMode)
	{
	case EWeaponMode::MainWeapon:
		ToggleSecondWeapon();
		break;
	case EWeaponMode::SecondWeapon:
		ToggleThirdWeapon();
		break;
	case EWeaponMode::ThirdWeapon:
		ToggleMainWeapon();
		break;
	}*/
}

void ADSPlayerCharacter::ToggleWeaponBegin()
{
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;

	/*switch (WeaponMode)
	{
	case EWeaponMode::MainWeapon:
		AttachWeapon(true, false, false);

		UKismetSystemLibrary::MoveComponentTo(MainWeaponSceneComponent, FVector::ZeroVector, FRotator::ZeroRotator,
			true,
			true, 0.2f, false, EMoveComponentAction::Type::Move, LatentActionInfo);

		break;
	case EWeaponMode::SecondWeapon:
		AttachWeapon(false, true, false);

		UKismetSystemLibrary::MoveComponentTo(SecondWeaponSceneComponent, FVector::ZeroVector, FRotator::ZeroRotator,
			true,
			true, 0.2f, false, EMoveComponentAction::Type::Move, LatentActionInfo);

		break;
	case EWeaponMode::ThirdWeapon:
		AttachWeapon(false, false, true);

		UKismetSystemLibrary::MoveComponentTo(ThirdWeaponSceneComponent, FVector::ZeroVector, FRotator::ZeroRotator,
			true,
			true, 0.2f, false, EMoveComponentAction::Type::Move, LatentActionInfo);

		break;
	}*/
}

void ADSPlayerCharacter::ToggleWeaponEnd()
{
	bToggleWeapon = false;

	bBeginThrowGrenade = false;

	bThrowingGrenade = false;

	bSpawnGrenade = false;
}

void ADSPlayerCharacter::Hit()
{
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientStartCameraShake(KnifeCameraShakeClass);

	const FVector HitLocation = KnifeSkeletalMeshComponent->GetSocketLocation(HitSocketName);
	const FRotator HitRotation = KnifeSkeletalMeshComponent->GetComponentRotation();
	FHitResult HitResult;
	const TArray<AActor*> IgnoreActors;
	//if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), HitLocation, HitLocation, 50.f, TraceType_Weapon, false,
	//	IgnoreActors, EDrawDebugTrace::None, HitResult, true))
	//{
	//	const EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());

	//	UGameplayStatics::ApplyDamage(HitResult.GetActor(), KnifeDamage, GetInstigatorController(), this,
	//		DamageTypeClass);

	//	// HitEffectComponent->PlayHitEffect(SurfaceType, HitLocation, HitRotation);
	//}
}

void ADSPlayerCharacter::FillUpWeaponBullet()
{
	/*CurrentMainWeapon->FillUpBullet();
	CurrentSecondWeapon->FillUpBullet();
	CurrentThirdWeapon->FillUpBullet();
	CurrentFPSCamera->FillUpBullet();*/
	GrenadeCount = MaxGrenadeCount;
}

void ADSPlayerCharacter::BeginThrowGrenade()
{
	if (!CheckStatus(false, false))
	{
		return;
	}

	if (bBeginThrowGrenade || bThrowingGrenade || GrenadeCount == 0)
	{
		return;
	}

	ToggleUseControlRotation(true);

	EndAction();

	bBeginThrowGrenade = true;

	AttachWeapon(false, false, false);

	PlayAnimMontage(ThrowGrenadeAnimMontage);
}

void ADSPlayerCharacter::EndThrowGrenade()
{
	bToggleWeapon = true;

	PlayAnimMontage(WeaponOutAnimMontage);

	ToggleUseControlRotation(false);
}

void ADSPlayerCharacter::ThrowGrenade()
{
	if (!CheckStatus(false, false))
	{
		return;
	}

	if (bThrowingGrenade || GrenadeCount == 0)
	{
		return;
	}

	EndAction();

	bThrowingGrenade = true;

	if (!bBeginThrowGrenade)
	{
		AttachWeapon(false, false, false);
	}

	if (!bSpawnGrenade)
	{
		SpawnGrenade();
	}

	PlayAnimMontage(ThrowGrenadeAnimMontage, 1, FName("Throw"));
}

void ADSPlayerCharacter::ThrowGrenadeOut()
{
	const FVector StartLocation = GrenadeSceneComponent->GetComponentLocation();

	const FVector CameraLocation = CameraComponent->GetComponentLocation();
	const FRotator CameraRotation = CameraComponent->GetComponentRotation();
	const FVector TargetLocation = CameraLocation + CameraRotation.Vector() * 3000.f;

	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

	/*CurrentGrenade->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentGrenade->ThrowGrenade(LookAtRotation, bFastRun || bJump);*/

	GrenadeCount = FMath::Clamp(GrenadeCount - 1, 0, MaxGrenadeCount);
}

void ADSPlayerCharacter::SpawnGrenade()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*CurrentGrenade = GetWorld()->SpawnActor<AMultiShootGameGrenade>(GrenadeClass, FVector::ZeroVector,
		FRotator::ZeroRotator, SpawnParameters);

	if (CurrentGrenade)
	{
		CurrentGrenade->BaseDamage = GrenadeDamage;
		CurrentGrenade->SetOwner(this);
		CurrentGrenade->AttachToComponent(GrenadeSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}*/

	bBeginThrowGrenade = true;

	bSpawnGrenade = true;
}

void ADSPlayerCharacter::KnifeAttack()
{
	if (!CheckStatus(false, true))
	{
		return;
	}

	EndAction();

	GetCharacterMovement()->SetMovementMode(MOVE_None);
	PlayAnimMontage(KnifeAttackAnimMontage, 2.0f);
}

void ADSPlayerCharacter::BeginKnifeAttack()
{
	bKnifeAttack = true;

	AttachWeapon(false, false, false);

	KnifeSkeletalMeshComponent->SetVisibility(true);
}

void ADSPlayerCharacter::EndKnifeAttack()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	bKnifeAttack = false;

	bToggleWeapon = true;

	KnifeSkeletalMeshComponent->SetVisibility(false);

	PlayAnimMontage(WeaponOutAnimMontage);
}

void ADSPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADSPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ADSPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADSPlayerCharacter::OnStartJump()
{
	bPressedJump = true;
}

void ADSPlayerCharacter::OnStopJump()
{
	bPressedJump = false;
}

bool ADSPlayerCharacter::CheckStatus(bool CheckAimed, bool CheckThrowGrenade)
{

	/*if (HealthComponent->bDied || bDetectingClimb || bReloading || bToggleWeapon || bSecondWeaponReloading ||
		bThrowingGrenade || bKnifeAttack)
	{
		return false;
	}*/

	/*if (CheckAimed && bAimed)
	{
		return false;
	}*/

	/*if (CheckThrowGrenade && bBeginThrowGrenade)
	{
		return false;
	}*/
	return true;
}

void ADSPlayerCharacter::EndAction()
{
	if (bAimed && !bSecondWeaponReloading)
	{
		EndAim();
	}

	if (bFired)
	{
		StopFire();
	}
}

void ADSPlayerCharacter::HandleWalkSpeed()
{
	if (bFastRun)
	{
		// GetCharacterMovement()->MaxWalkSpeed = WeaponMode != EWeaponMode::SecondWeapon ? 600.f : 500.f;
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		// GetCharacterMovement()->MaxWalkSpeed = WeaponMode != EWeaponMode::SecondWeapon ? 300.f : 250.f;
	}
}

void ADSPlayerCharacter::AttachWeapon(bool MainWeapon, bool SecondWeapon, bool ThirdWeapon)
{
	MainWeaponSceneComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
		MainWeapon ? MainWeaponSocketName : BackMainWeaponSocketName);

	SecondWeaponSceneComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
		SecondWeapon ? SecondWeaponSocketName : BackSecondWeaponSocketName);

	ThirdWeaponSceneComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		ThirdWeapon ? ThirdWeaponSocketName : BackThirdWeaponSocketName);
}

void ADSPlayerCharacter::ToggleUseControlRotation(bool Enabled)
{
	/*if (WeaponMode == EWeaponMode::MainWeapon)
	{*/
	bUseControlRotation = Enabled;
	/*}*/
}

void ADSPlayerCharacter::Death()
{
	// HealthComponent->bDied = true;

	EndAction();

	ToggleUseControlRotation(true);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMovementComponent()->SetActive(false);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetAllBodiesPhysicsBlendWeight(DeathRagdollWeight);
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetMesh()->GetAnimInstance()->StopAllMontages(0);

	/*CurrentMainWeapon->EnablePhysicsSimulate();
	CurrentSecondWeapon->EnablePhysicsSimulate();
	CurrentThirdWeapon->EnablePhysicsSimulate();*/

	DeathAudioComponent->Play();
}
// Called when the game starts or when spawned
// Called every frame
void ADSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bMoving = GetCharacterMovement()->Velocity.Size() > 0;

	if (bAimed)
	{
		const FVector StartLocation = FPSCameraSceneComponent->GetComponentLocation();

		const FVector CameraLocation = CameraComponent->GetComponentLocation();
		const FRotator CameraRotation = CameraComponent->GetComponentRotation();
		const FVector TargetLocation = CameraLocation + CameraRotation.Vector() * 3000.f;

		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

		const FRotator TargetRotation = FRotator(0, LookAtRotation.Yaw - 90.f, LookAtRotation.Pitch * -1.f);

		FPSCameraSceneComponent->SetWorldRotation(TargetRotation);
	}

	/*if (WeaponMode == EWeaponMode::MainWeapon && (bUseControlRotation ||
		(!bUseControlRotation && GetMovementComponent()->Velocity.Size() != 0)))*/
	if ((bUseControlRotation ||(!bUseControlRotation && GetMovementComponent()->Velocity.Size() != 0)))
	{
		const FRotator TargetRotation = FRotator(0, GetControlRotation().Yaw, 0);
		const FRotator Rotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 15);
		SetActorRotation(Rotation);
	}
}

// Called to bind functionality to input
void ADSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADSPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADSPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ADSPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ADSPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADSPlayerCharacter::TurnAtRate);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADSPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADSPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("FastRun", IE_Pressed, this, &ADSPlayerCharacter::BeginFastRun);
	PlayerInputComponent->BindAction("FastRun", IE_Released, this, &ADSPlayerCharacter::EndFastRun);


	// Bind aim events
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ADSPlayerCharacter::BeginAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ADSPlayerCharacter::EndAim);


	// Bind crouch events
	PlayerInputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &ADSPlayerCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADSPlayerCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADSPlayerCharacter::EndCrouch);

	// Bind reloading events
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ADSPlayerCharacter::BeginReload);


	// Bind toggle weapon events
	/*PlayerInputComponent->BindAction("MainWeapon", IE_Pressed, this, &ADSPlayerCharacter::ToggleMainWeapon);
	PlayerInputComponent->BindAction("SecondWeapon", IE_Pressed, this, &ADSPlayerCharacter::ToggleSecondWeapon);
	PlayerInputComponent->BindAction("ThirdWeapon", IE_Pressed, this, &ADSPlayerCharacter::ToggleThirdWeapon);
	PlayerInputComponent->BindAction("ToggleWeaponUp", IE_Pressed, this, &ADSPlayerCharacter::ToggleWeaponUp);
	PlayerInputComponent->BindAction("ToggleWeaponDown", IE_Pressed, this, &ADSPlayerCharacter::ToggleWeaponDown);*/

	
	// Bind throw grenade
	PlayerInputComponent->BindAction("ThrowGrenade", IE_Pressed, this, &ADSPlayerCharacter::BeginThrowGrenade);
	PlayerInputComponent->BindAction("ThrowGrenade", IE_Released, this, &ADSPlayerCharacter::ThrowGrenade);

	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

USceneComponent* ADSPlayerCharacter::GetFPSCameraSceneComponent() const
{
	return FPSCameraSceneComponent;
}

UCameraComponent* ADSPlayerCharacter::GetCameraComponent() const
{
	return CameraComponent;
}

bool ADSPlayerCharacter::GetAimed() const
{
	return bAimed;
}
//
//EWeaponMode AMultiShootGameCharacter::GetWeaponMode() const
//{
//	return WeaponMode;
//}

void ADSPlayerCharacter::SetEnableMovement(bool Value)
{
	bEnableMovement = Value;
}

//
//UHealthComponent* AMultiShootGameCharacter::GetHealthComponent() const
//{
//	return HealthComponent;
//}
