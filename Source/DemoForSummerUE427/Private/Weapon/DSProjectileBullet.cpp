// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DSProjectileBullet.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "DemoForSummerUE427/DemoForSummerUE427.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include <GamePlay/DSGameMode.h>
#include <Common/DSHelper.h>

ADSProjectileBullet::ADSProjectileBullet()
{
	// Use a sphere as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");


	// Players can't walk on it
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;

	// CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetEnableGravity(true);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// CollisionComponent->SetCollisionResponseToAllChannels(ECR_MAX)
	/*CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->bReturnMaterialOnMove = true;*/


	// Set as root component
	RootComponent = CollisionComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(
		TEXT("StaticMesh'/Game/Map/Sphere.Sphere'")
	);
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeScale3D(FVector(0.3f));
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	//ParticleSystemComponent->SetupAttachment(CollisionComponent);

	// HitEffectComponent = CreateDefaultSubobject<UDSHitEffectComponent>(TEXT("HitEffectComponent"));


	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 4000.f;
	ProjectileMovement->MaxSpeed = 4000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	// ProjectileMovement->ProjectileGravityScale = 1.0;


	// DSHelper::Debug(FString::Printf(TEXT("ADSProjectileBullet:: ADSProjectileBullet")), 5);
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ADSProjectileBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DSHelper::Debug(FString::Printf(TEXT("ADSProjectileBullet:: OnHit")), 5);
	//const EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

	//if (Cast<ACharacter>(OtherActor))
	//{
	//	if (SurfaceType == SURFACE_HEAD)
	//	{
	//		BaseDamage *= 2.5f;
	//		// Cast<ADSGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OnHeadshot();
	//	}

	//	UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, GetActorRotation().Vector(), Hit,
	//		GetOwner()->GetInstigatorController(), GetOwner(), DamageTypeClass);
	//}
	//else
	//{
	//	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics()) {

	//		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	//	}
	//	UGameplayStatics::SpawnDecalAttached(BulletDecalMaterial, BulletDecalSize, OtherComp, NAME_None, Hit.Location,
	//		Hit.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 10.f);
	//}

	//HitEffectComponent->PlayHitEffect(SurfaceType, Hit.Location, GetActorRotation());

	Destroy();
}

void ADSProjectileBullet::OnOverlap(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DSHelper::Debug(FString::Printf(TEXT("ADSProjectileBullet:: OnOverlap")), 5);
	const EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(SweepResult.PhysMaterial.Get());

	if (Cast<ACharacter>(OtherActor))
	{
		if (SurfaceType == SURFACE_HEAD)
		{
			BaseDamage *= 2.5f;
			// Cast<ADSGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->OnHeadshot();
		}

		UGameplayStatics::ApplyPointDamage(OtherActor, BaseDamage, GetActorRotation().Vector(), SweepResult,
			GetOwner()->GetInstigatorController(), GetOwner(), DamageTypeClass);
	}
	else
	{
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComponent != nullptr) && OtherComponent->IsSimulatingPhysics()) {

			OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
		UGameplayStatics::SpawnDecalAttached(BulletDecalMaterial, BulletDecalSize, OtherComponent, NAME_None, SweepResult.Location,
			SweepResult.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 10.f);
	}

	// HitEffectComponent->PlayHitEffect(SurfaceType, SweepResult.Location, GetActorRotation());

	Destroy();
}

void ADSProjectileBullet::BeginPlay()
{

	Super::BeginPlay();

	DSHelper::Debug(FString::Printf(TEXT("ADSProjectileBullet:: BeginPlay")), 5);
	// BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &ADSProjectileBullet::OnOverlap);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADSProjectileBullet::OnOverlap);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ADSProjectileBullet::OnHit);
}
