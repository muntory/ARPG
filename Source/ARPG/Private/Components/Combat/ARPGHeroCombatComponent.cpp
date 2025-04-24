// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/ARPGHeroCombatComponent.h"
#include "Items/Weapons/ARPGHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ARPGGameplayTags.h"

#include "ARPGDebugHelper.h"
AARPGHeroWeapon* UARPGHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AARPGHeroWeapon>(GetCarriedWeaponByTag(InWeaponTag));
}

AARPGHeroWeapon* UARPGHeroCombatComponent::GetHeroCurrentEquippingWeapon() const
{
    return Cast<AARPGHeroWeapon>(GetCurrentEquippingWeapon());
}

float UARPGHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
    return GetHeroCurrentEquippingWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UARPGHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        ARPGGameplayTags::Shared_Event_MeleeHit,
        Data
    );

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        ARPGGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}

void UARPGHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        ARPGGameplayTags::Player_Event_HitPause,
        FGameplayEventData()
    );
}
