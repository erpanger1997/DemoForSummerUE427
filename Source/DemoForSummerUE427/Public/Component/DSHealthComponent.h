// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOFORSUMMERUE427_API UDSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UDSHealthComponent*, OwningHealthComponent,
														float, Health, float, HealthDelta, const class UDamageType*,
														DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);
public:	
	// Sets default values for this component's properties
	UDSHealthComponent();

	float GetHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Health)
		static bool IsFriendly(AActor* ActorA, AActor* ActorB);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void Heal(float HealAmount);

	UFUNCTION()
		void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser);

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		bool bDied = false;


	UPROPERTY(BlueprintAssignable, Category = Events)
		FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
		uint8 TeamNumber = 0;

protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
		float DefaultHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float CurrentHealth = DefaultHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
		UAnimMontage* HitHeadMontage;

};
