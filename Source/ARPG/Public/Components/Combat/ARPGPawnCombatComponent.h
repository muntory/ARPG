// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ARPGPawnComponentBase.h"
#include "GameplayTagContainer.h"
#include "ARPGPawnCombatComponent.generated.h"

class AARPGBaseWeapon;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class ARPG_API UARPGPawnCombatComponent : public UARPGPawnComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AARPGBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGBaseWeapon* GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "ARPG|Combat")
	FGameplayTag CurrentEquippingWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	AARPGBaseWeapon* GetCurrentEquippingWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "ARPG|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	TArray<AActor*> OverlappedActors;
private:
	TMap<FGameplayTag, AARPGBaseWeapon*> TagToEquippableWeaponMap;
};
