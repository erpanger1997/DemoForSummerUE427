// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// #include "../Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/MatineeCameraShake.h"
#include "DSPlayerCharacter.generated.h"
//#include "Runtime/Engine/Classes/Components/ChildActorComponent.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DEMOFORSUMMERUE427_API ADSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BeginReload();

	USceneComponent* GetFPSCameraSceneComponent() const;

	UCameraComponent* GetCameraComponent() const;

	/*UPROPERTY(BlueprintReadOnly)
		AMultiShootGameWeapon* CurrentMainWeapon;

	UPROPERTY(BlueprintReadOnly)
		AMultiShootGameWeapon* CurrentSecondWeapon;

	UPROPERTY(BlueprintReadOnly)
		AMultiShootGameWeapon* CurrentThirdWeapon;

	UPROPERTY(BlueprintReadOnly)
		AMultiShootGameFPSCamera* CurrentFPSCamera;*/

	bool GetAimed() const;

	//EWeaponMode GetWeaponMode() const;

	void SetEnableMovement(bool Value);

	//UHealthComponent* GetHealthComponent() const;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


	void StartFire();					// 开火

	void StopFire();					// 停火

	void MoveForward(float Value);		// 纵向移动

	void MoveRight(float Value);		// 横向移动

	void BeginFastRun();				// 加速跑

	void EndFastRun();					// 停止加速

	void BeginCrouch();					// 下蹲

	void EndCrouch();					// 结束下蹲

	void ToggleCrouch();				// 切换下蹲姿势

	void BeginAim();

	void EndAim();

	void LookUpAtRate(float Value);
	
	void Turn(float Value);
	
	void TurnAtRate(float Value);
	
	void OnStartJump();
	
	void OnStopJump();

	void BeginSecondWeaponReload();

	UFUNCTION(BlueprintCallable)
		void EndReload();

	UFUNCTION(BlueprintCallable)
		void ReloadShowClip(bool Enabled);

	void ToggleMainWeapon();

	void ToggleSecondWeapon();

	void ToggleThirdWeapon();

	void ToggleWeaponUp();

	void ToggleWeaponDown();

	UFUNCTION(BlueprintCallable)
		void ToggleWeaponBegin();

	UFUNCTION(BlueprintCallable)
		void ToggleWeaponEnd();

	UFUNCTION(BlueprintCallable)
		void Hit();

	UFUNCTION(BlueprintCallable)
		void FillUpWeaponBullet();

	void ToggleUseControlRotation(bool Enabled);

	UFUNCTION(BlueprintCallable)
		bool CheckStatus(bool CheckAimed, bool CheckThrowGrenade);

	/*UFUNCTION()
		void OnHealthChanged(UHealthComponent* OwningHealthComponent, float Health, float HealthDelta,
			const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);*/


	void BeginThrowGrenade();

	UFUNCTION(BlueprintCallable)
		void EndThrowGrenade();

	void ThrowGrenade();

	UFUNCTION(BlueprintCallable)
		void ThrowGrenadeOut();

	UFUNCTION(BlueprintCallable)
		void SpawnGrenade();

	void KnifeAttack();

	UFUNCTION(BlueprintCallable)
		void BeginKnifeAttack();

	UFUNCTION(BlueprintCallable)
		void EndKnifeAttack();

	UFUNCTION(BlueprintCallable)
		void EndAction();

	void HandleWalkSpeed();

	UFUNCTION(BlueprintCallable)
		void AttachWeapon(bool MainWeapon, bool SecondWeapon, bool ThirdWeapon);

	UFUNCTION(BlueprintCallable)
		void Death();

public:

	class ADSPlayerController* SPController;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* FPSCameraSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* MainWeaponSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* SecondWeaponSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* ThirdWeaponSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* GrenadeSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USkeletalMeshComponent* KnifeSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UAudioComponent* DeathAudioComponent;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UHitEffectComponent* HitEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<AMultiShootGameWeapon> MainWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<AMultiShootGameWeapon> SecondWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<AMultiShootGameWeapon> ThirdWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<AMultiShootGameGrenade> GrenadeClass;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName MainWeaponSocketName = "MainWeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName BackMainWeaponSocketName = "BackMainWeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName SecondWeaponSocketName = "SecondWeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName BackSecondWeaponSocketName = "BackSecondWeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName ThirdWeaponSocketName = "ThirdWeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName BackThirdWeaponSocketName = "BackThirdWeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName GrenadeSocketName = "GrenadeSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName KnifeSocketName = "KnifeSocket";

	UPROPERTY(EditDefaultsOnly, Category = Character)
		FName HitSocketName = "HitSocket";

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<AMultiShootGameFPSCamera> FPSCameraClass;*/

	/*UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> MovementCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> FPSCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> KnifeCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> HitCameraShakeClass;*/

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* WeaponOutAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* SecondWeaponReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* ThirdWeaponReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* ThrowGrenadeAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* KnifeAttackAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<UUserWidget> GameUserWidgetClass; // 正常模式下widget对象指针

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<UUserWidget> SniperUserWidgetClass; // 狙击模式widget对象指针

	/*UPROPERTY(BlueprintReadOnly, Category = Character)
		EWeaponMode WeaponMode = EWeaponMode::MainWeapon;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		float KnifeDamage = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		float GrenadeDamage = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		float CameraPitchClamp = 60.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		float MaxDeadTimeDilationDelay = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		int MaxGrenadeCount = 4; // 手雷数量

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		float DeathRagdollWeight = 0.3;

	/*UPROPERTY(BlueprintReadOnly)
		AMultiShootGameGrenade* CurrentGrenade;*/

	UPROPERTY(BlueprintReadOnly)
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite)
		bool bDetectingClimb = false;

	UPROPERTY(BlueprintReadOnly)
		bool bAimed = false;

	UPROPERTY(BlueprintReadWrite)
		bool bEnableMovement = true;

	UPROPERTY(BlueprintReadOnly)
		int GrenadeCount;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* CurrentGameUserWidget;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* CurrentSniperUserWidget;


private:

	// 手上物品
	UPROPERTY(VisibleDefaultsOnly, Category = "DemoSummer")
		class UChildActorComponent* HandObject;

	float BaseLookUpRate;

	float BaseTurnRate;

	bool bFired = false;

	bool bFastRun = false;

	bool bJump = false;


	bool bReloading = false;

	bool bSecondWeaponReloading = false;

	bool bToggleWeapon = false;

	bool bBeginThrowGrenade = false;

	bool bThrowingGrenade = false;

	bool bSpawnGrenade = false;

	bool bKnifeAttack = false;

	bool bUseControlRotation = false;



};
