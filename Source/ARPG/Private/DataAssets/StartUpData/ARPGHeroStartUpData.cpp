// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/ARPGHeroStartUpData.h"
#include "AbilitySystem/Abilities/ARPGHeroGameplayAbility.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "ARPGTypes/ARPGStructTypes.h"


void UARPGHeroStartUpData::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

    for (const FARPGHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        InASCToGive->GiveAbility(AbilitySpec);
    }
}
