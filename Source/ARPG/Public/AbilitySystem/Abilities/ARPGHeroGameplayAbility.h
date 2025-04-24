// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "ARPGHeroGameplayAbility.generated.h"

class AARPGHeroCharacter;
class AARPGHeroController;
class UARPGHeroCombatComponent;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGHeroGameplayAbility : public UARPGGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	AARPGHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	UARPGHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "ARPG|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

protected:

	
private:
	TWeakObjectPtr<AARPGHeroCharacter> CachedARPGHeroCharacter;
	TWeakObjectPtr<AARPGHeroController> CachedARPGHeroController;

};
