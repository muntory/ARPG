// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/ARPGStartUpDataBase.h"
#include "ARPGEnemyStartUpData.generated.h"

class UARPGEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGEnemyStartUpData : public UARPGStartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UARPGAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UARPGEnemyGameplayAbility>> EnemyCombatAbilities;

	
};
