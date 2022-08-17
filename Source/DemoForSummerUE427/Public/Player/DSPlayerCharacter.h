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


	void StartFire();					// ����

	void StopFire();					// ͣ��

	void MoveForward(float Value);		// �����ƶ�

	void MoveRight(float Value);		// �����ƶ�

	void BeginFastRun();				// ������

	void EndFastRun();					// ֹͣ����

	void BeginCrouch();					// �¶�

	void EndCrouch();					// �����¶�

	void ToggleCrouch();				// �л��¶�����

	void BeginAim();					// ��ʼ��׼

	void EndAim();						// ������׼

	void LookUpAtRate(float Value);		// �ӽ�����ת��
	
	void Turn(float Value);				// �ӽǺ���ת��
	
	void TurnAtRate(float Value);		// �ӽǺ���ת��
	
	// void OnStartJump();					// ��ʼ��Ծ
	
	// void OnStopJump();					// ������Ծ

	void BeginSecondWeaponReload();			// �ڶ�����������װ��

	UFUNCTION(BlueprintCallable)
		void EndReload();					// ����װ��

	UFUNCTION(BlueprintCallable)
		void ReloadShowClip(bool Enabled);	// ����װ������ʾ����

	void ToggleMainWeapon();				// �л�Ϊ������

	void ToggleSecondWeapon();				// �л�Ϊ������

	void ToggleThirdWeapon();				// �л�Ϊ��ǹ

	void ToggleWeaponUp();					// �����л�����

	void ToggleWeaponDown();				// �����л�����

	UFUNCTION(BlueprintCallable)
		void ToggleWeaponBegin();			// ��ʼ�л�����

	UFUNCTION(BlueprintCallable)
		void ToggleWeaponEnd();				// �����л�����

	UFUNCTION(BlueprintCallable)
		void Hit();							// ���

	UFUNCTION(BlueprintCallable)
		void FillUpWeaponBullet();			// װ�������ӵ�

	void ToggleUseControlRotation(bool Enabled);	// �л��Ƿ��ܹ�����ת��

	UFUNCTION(BlueprintCallable)
		bool CheckStatus(bool CheckAimed, bool CheckThrowGrenade);	//	 ״̬���

	UFUNCTION()
		void OnHealthChanged(UDSHealthComponent* OwningHealthComponent, float Health, float HealthDelta,
			const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	void BeginThrowGrenade();				// ��ʼ����

	UFUNCTION(BlueprintCallable)
		void EndThrowGrenade();				// ��������

	void ThrowGrenade();					// ���ף����ڲ��Ŷ���

	UFUNCTION(BlueprintCallable)
		void ThrowGrenadeOut();				// �ӳ�����

	UFUNCTION(BlueprintCallable)
		void SpawnGrenade();				// ��������

	void KnifeAttack();						// ��ս����

	UFUNCTION(BlueprintCallable)
		void BeginKnifeAttack();			// ��ʼ��ս����

	UFUNCTION(BlueprintCallable)
		void EndKnifeAttack();				// ������ս����

	UFUNCTION(BlueprintCallable)
		void EndAction();					// ������ǰ����

	void HandleWalkSpeed();					// �����н��ٶ�

	UFUNCTION(BlueprintCallable)
		void AttachWeapon(bool MainWeapon, bool SecondWeapon, bool ThirdWeapon);	// װ������

	UFUNCTION(BlueprintCallable)
		void Death();						// ����


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
	//	TSubclassOf<UUserWidget> GameUserWidgetClass; // ����ģʽ��widget����ָ��

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	//	TSubclassOf<UUserWidget> SniperUserWidgetClass; // �ѻ�ģʽwidget����ָ��

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
		int MaxGrenadeCount = 4; // ��������

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

	// ������Ʒ
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
