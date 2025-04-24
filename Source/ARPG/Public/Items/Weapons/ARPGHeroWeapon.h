// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/ARPGBaseWeapon.h"
#include "ARPGTypes/ARPGStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "ARPGHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroWeapon : public AARPGBaseWeapon
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FARPGHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
