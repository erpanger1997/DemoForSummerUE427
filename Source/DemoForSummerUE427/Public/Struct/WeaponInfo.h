// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include <MatineeCameraShake.h>
#include <Weapon/DSProjectileBase.h>
#include "WeaponInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEMOFORSUMMERUE427_API FWeaponInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		FString Name;				// ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		USkeletalMesh* WeaponMesh;	// ����mesh

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		UTexture* WeaponImage;		// ��������ͼ

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		UStaticMesh* MagazineClipMesh;	// ����mesh

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		TSubclassOf<ADSProjectileBase> ProjectileClass; // �ӵ���

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		TSubclassOf<UMatineeCameraShake> FireCameraShake;	// ��Ļ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float BaseDamage;			// �����˺�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float RateOfFire;			// ��������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float DelayOfShotgun;		// �����ӳ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float BulletSpread;			// �ӵ�ƫ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float CameraSpread;			// ��ͷƫ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float CameraSpreadDown;		// ����ͷƫ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		FVector AimVector;			// ��׼����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		bool AimTexture;			// �Ƿ���Ҫ��Ⱦ��һ�ӽ�����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int BulletNumber;			// ��ǰ����ʣ���ӵ���

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int FillUpBulletNumber;		// ��������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int MaxBulletNumber;		// ��󱸵�����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int FillUpMaxBulletNumber;	// ������������
};
