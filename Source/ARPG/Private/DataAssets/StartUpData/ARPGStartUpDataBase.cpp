// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/ARPGStartUpDataBase.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"

void UARPGStartUpDataBase::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(StartUpOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(StartUpOnTriggeredAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UARPGStartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UARPGGameplayAbility>>& InAbilitiesToGrant, UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGrant.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UARPGGameplayAbility>& Ability : InAbilitiesToGrant)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
