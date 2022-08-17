// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DSHealthComponent.h"

// Sets default values for this component's properties
UDSHealthComponent::UDSHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UDSHealthComponent::HandleTakeAnyDamage);
	}
}


void UDSHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0 || CurrentHealth <= 0)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, DefaultHealth);

	OnHealthChanged.Broadcast(this, CurrentHealth, -HealAmount, nullptr, nullptr, nullptr);
}

void UDSHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bDied)
	{
		return;
	}

	//if (DamageCauser != DamagedActor && IsFriendly(DamageCauser, DamagedActor))
	//{
	//	return;
	//}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

	OnHealthChanged.Broadcast(this, CurrentHealth, Damage, DamageType, InstigatedBy, DamageCauser);
}


float UDSHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

bool UDSHealthComponent::IsFriendly(AActor* ActorA, AActor* ActorB)
{
	if (ActorA == nullptr || ActorB == nullptr)
	{
		return true;
	}

	UDSHealthComponent* HealthComponentA = Cast<UDSHealthComponent>(
		ActorA->GetComponentByClass(UDSHealthComponent::StaticClass()));
	UDSHealthComponent* HealthComponentB = Cast<UDSHealthComponent>(
		ActorB->GetComponentByClass(UDSHealthComponent::StaticClass()));

	if (HealthComponentA == nullptr || HealthComponentB == nullptr)
	{
		return true;
	}

	return HealthComponentA->TeamNumber == HealthComponentB->TeamNumber;
}

