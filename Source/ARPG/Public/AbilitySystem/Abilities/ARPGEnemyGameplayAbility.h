// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "ARPGEnemyGameplayAbility.generated.h"

class AARPGEnemyCharacter;
class UARPGEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGEnemyGameplayAbility : public UARPGGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	UARPGEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AARPGEnemyCharacter> CachedARPGEnemyCharacter;
};
