// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Weapon/DSWeapon.h>
#include <Enum/EWeaponMode.h>
#include <Weapon/DSFirstWeapon.h>
#include <MatineeCameraShake.h>
// #include "../Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/MatineeCameraShake.h"
#include "DSPlayerCharacter.generated.h"
//#include "Runtime/Engine/Classes/Components/ChildActorComponent.h"

class UCameraComponent;
class USpringArmComponent;
class UDSHitEffectComponent;
class UDSHealthComponent;

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
	

	bool GetAimed() const;

	EWeaponMode GetWeaponMode() const;

	void SetEnableMovement(bool Value);

	UDSHealthComponent* GetHealthComponent() const;

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

	void BeginAim();					// 开始瞄准

	void EndAim();						// 结束瞄准

	void LookUpAtRate(float Value);		// 视角纵向转换
	
	void Turn(float Value);				// 视角横向转换
	
	void TurnAtRate(float Value);		// 视角横向转换
	
	// void OnStartJump();					// 开始跳跃
	
	// void OnStopJump();					// 结束跳跃

	void BeginSecondWeaponReload();			// 第二把武器重新装弹

	UFUNCTION(BlueprintCallable)
		void EndReload();					// 结束装弹

	UFUNCTION(BlueprintCallable)
		void ReloadShowClip(bool Enabled);	// 重新装弹后显示弹夹

	void ToggleMainWeapon();				// 切换为主武器

	void ToggleSecondWeapon();				// 切换为副武器

	void ToggleThirdWeapon();				// 切换为手枪

	void ToggleWeaponUp();					// 向上切换武器

	void ToggleWeaponDown();				// 向下切换武器

	UFUNCTION(BlueprintCallable)
		void ToggleWeaponBegin();			// 开始切换武器

	UFUNCTION(BlueprintCallable)
		void ToggleWeaponEnd();				// 结束切换武器

	UFUNCTION(BlueprintCallable)
		void Hit();							// 射击

	UFUNCTION(BlueprintCallable)
		void FillUpWeaponBullet();			// 装满所有子弹

	void ToggleUseControlRotation(bool Enabled);	// 切换是否能够控制转向

	UFUNCTION(BlueprintCallable)
		bool CheckStatus(bool CheckAimed, bool CheckThrowGrenade);	//	 状态检查

	UFUNCTION()
		void OnHealthChanged(UDSHealthComponent* OwningHealthComponent, float Health, float HealthDelta,
			const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	void BeginThrowGrenade();				// 开始扔雷

	UFUNCTION(BlueprintCallable)
		void EndThrowGrenade();				// 结束扔雷

	void ThrowGrenade();					// 扔雷，用于播放动画

	UFUNCTION(BlueprintCallable)
		void ThrowGrenadeOut();				// 扔出手雷

	UFUNCTION(BlueprintCallable)
		void SpawnGrenade();				// 生成手雷

	void KnifeAttack();						// 近战攻击

	UFUNCTION(BlueprintCallable)
		void BeginKnifeAttack();			// 开始近战攻击

	UFUNCTION(BlueprintCallable)
		void EndKnifeAttack();				// 结束近战攻击

	UFUNCTION(BlueprintCallable)
		void EndAction();					// 结束当前动作

	void HandleWalkSpeed();					// 设置行进速度

	UFUNCTION(BlueprintCallable)
		void AttachWeapon(bool MainWeapon, bool SecondWeapon, bool ThirdWeapon);	// 装备武器

	UFUNCTION(BlueprintCallable)
		void Death();						// 死亡


public:

	class ADSPlayerController* SPController;

	UPROPERTY(BlueprintReadOnly)
		ADSWeapon* CurrentMainWeapon;

	UPROPERTY(BlueprintReadOnly)
		ADSWeapon* CurrentSecondWeapon;

	UPROPERTY(BlueprintReadOnly)
		ADSWeapon* CurrentThirdWeapon;

	UPROPERTY(BlueprintReadOnly)
		ADSFirstWeapon* CurrentFPSCamera;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* FPSCameraSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* MainWeaponSceneComponent;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* SecondWeaponSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* ThirdWeaponSceneComponent;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USceneComponent* GrenadeSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		USkeletalMeshComponent* KnifeSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UAudioComponent* DeathAudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UDSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		UDSHitEffectComponent* HitEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<ADSWeapon> MainWeaponClass;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<ADSWeapon> SecondWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<ADSWeapon> ThirdWeaponClass;*/

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
		TSubclassOf<ADSFirstWeapon> FPSCameraClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> MovementCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> FPSCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> KnifeCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		TSubclassOf<UMatineeCameraShake> HitCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* WeaponOutAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Character)
		UAnimMontage* ReloadAnimMontage;

	//UPROPERTY(EditDefaultsOnly, Category = Character)
	//	UAnimMontage* SecondWeaponReloadAnimMontage;

	//UPROPERTY(EditDefaultsOnly, Category = Character)
	//	UAnimMontage* ThirdWeaponReloadAnimMontage;

	//UPROPERTY(EditDefaultsOnly, Category = Character)
	//	UAnimMontage* ThrowGrenadeAnimMontage;

	//UPROPERTY(EditDefaultsOnly, Category = Character)
	//	UAnimMontage* KnifeAttackAnimMontage;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	//	TSubclassOf<UUserWidget> GameUserWidgetClass; // 正常模式下widget对象指针

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	//	TSubclassOf<UUserWidget> SniperUserWidgetClass; // 狙击模式widget对象指针

	UPROPERTY(BlueprintReadOnly, Category = Character)
		EWeaponMode WeaponMode = EWeaponMode::MainWeapon;

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

	/*UPROPERTY(BlueprintReadOnly)
		UUserWidget* CurrentGameUserWidget;

	UPROPERTY(BlueprintReadOnly)
		UUserWidget* CurrentSniperUserWidget;*/


private:

	// 手上物品
	/*UPROPERTY(VisibleDefaultsOnly, Category = "DemoSummer")
		class UChildActorComponent* HandObject;*/

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
