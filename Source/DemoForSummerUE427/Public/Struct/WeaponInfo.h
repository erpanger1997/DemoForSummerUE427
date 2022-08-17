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
		FString Name;				// 武器名

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		USkeletalMesh* WeaponMesh;	// 武器mesh

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		UTexture* WeaponImage;		// 武器缩略图

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		UStaticMesh* MagazineClipMesh;	// 弹夹mesh

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		TSubclassOf<ADSProjectileBase> ProjectileClass; // 子弹类

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		TSubclassOf<UMatineeCameraShake> FireCameraShake;	// 屏幕抖动

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float BaseDamage;			// 基础伤害

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float RateOfFire;			// 基础射速

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float DelayOfShotgun;		// 开火延迟

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float BulletSpread;			// 子弹偏移

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float CameraSpread;			// 镜头偏移

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		float CameraSpreadDown;		// 竖向镜头偏移

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		FVector AimVector;			// 瞄准方向

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		bool AimTexture;			// 是否需要渲染第一视角武器

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int BulletNumber;			// 当前弹夹剩余子弹数

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int FillUpBulletNumber;		// 弹夹容量

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int MaxBulletNumber;		// 最大备弹数量

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WeaponInfo)
		int FillUpMaxBulletNumber;	// 填满备弹数量
};
