// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ARPGPawnCombatComponent.h"
#include "GameplayTagContainer.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/ARPGBaseWeapon.h"

#include "ARPGDebugHelper.h"

void UARPGPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AARPGBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!TagToEquippableWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named %s already has been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	TagToEquippableWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippingWeaponTag = InWeaponTagToRegister;
	}
}

AARPGBaseWeapon* UARPGPawnCombatComponent::GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (TagToEquippableWeaponMap.Contains(InWeaponTagToGet))
	{
		return *TagToEquippableWeaponMap.Find(InWeaponTagToGet);
	}

	return nullptr;
}

AARPGBaseWeapon* UARPGPawnCombatComponent::GetCurrentEquippingWeapon() const
{
	if (!CurrentEquippingWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCarriedWeaponByTag(CurrentEquippingWeaponTag);
}

void UARPGPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AARPGBaseWeapon* WeaponToToggle = GetCurrentEquippingWeapon();
		check(WeaponToToggle);

		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionbox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionbox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}

	// todo : handle body collision boxes
}

void UARPGPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{

}

void UARPGPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
