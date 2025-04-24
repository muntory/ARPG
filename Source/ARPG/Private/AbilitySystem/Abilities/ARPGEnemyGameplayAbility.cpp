// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGEnemyGameplayAbility.h"
#include "Chracters/ARPGEnemyCharacter.h"

AARPGEnemyCharacter* UARPGEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedARPGEnemyCharacter.IsValid())
    {
        CachedARPGEnemyCharacter = Cast<AARPGEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedARPGEnemyCharacter.IsValid() ? CachedARPGEnemyCharacter.Get() : nullptr;
}

UARPGEnemyCombatComponent* UARPGEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
