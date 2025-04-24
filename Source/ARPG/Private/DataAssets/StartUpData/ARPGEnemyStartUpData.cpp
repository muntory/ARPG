// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/ARPGEnemyStartUpData.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ARPGEnemyGameplayAbility.h"

void UARPGEnemyStartUpData::GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UARPGEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
