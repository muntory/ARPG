// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ARPGStartUpDataBase.generated.h"

class UARPGGameplayAbility;
class UARPGAbilitySystemComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGStartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UARPGGameplayAbility>> StartUpOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UARPGGameplayAbility>> StartUpOnTriggeredAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UARPGGameplayAbility>>& InAbilitiesToGrant, UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
