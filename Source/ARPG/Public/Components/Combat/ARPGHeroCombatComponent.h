// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/ARPGPawnCombatComponent.h"
#include "ARPGHeroCombatComponent.generated.h"

class AARPGHeroWeapon;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGHeroCombatComponent : public UARPGPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGHeroWeapon* GetHeroCurrentEquippingWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
