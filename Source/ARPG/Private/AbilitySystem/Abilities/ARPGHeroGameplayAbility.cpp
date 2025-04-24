// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGHeroGameplayAbility.h"
#include "Chracters/ARPGHeroCharacter.h"
#include "Controllers/ARPGHeroController.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "ARPGGameplayTags.h"


AARPGHeroCharacter* UARPGHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedARPGHeroCharacter.IsValid())
    {
        CachedARPGHeroCharacter = Cast<AARPGHeroCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedARPGHeroCharacter.IsValid() ? CachedARPGHeroCharacter.Get() : nullptr;
}

AARPGHeroController* UARPGHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedARPGHeroController.IsValid())
    {
        CachedARPGHeroController = Cast<AARPGHeroController>(CurrentActorInfo->PlayerController);
    }

    return CachedARPGHeroController.IsValid() ? CachedARPGHeroController.Get() : nullptr;
}

UARPGHeroCombatComponent* UARPGHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UARPGHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
    check(EffectClass);

    FGameplayEffectContextHandle ContextHandle = GetARPGAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle EffectSpecHandle = GetARPGAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(),
        ContextHandle
    );

    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        ARPGGameplayTags::Shared_SetByCaller_BaseDamage,
        InWeaponBaseDamage
    );

    if (InCurrentAttackTypeTag.IsValid())
    {
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
    }

    return EffectSpecHandle;
}
