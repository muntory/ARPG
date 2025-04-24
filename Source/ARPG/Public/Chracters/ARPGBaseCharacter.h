// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "ARPGBaseCharacter.generated.h"

class UARPGAbilitySystemComponent;
class UARPGAttributeSet;
class UARPGStartUpDataBase;
UCLASS()
class ARPG_API AARPGBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPGBaseCharacter();

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

#pragma region AbilitySystem
public:
	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	FORCEINLINE UARPGAbilitySystemComponent* GetARPGAbilitySystemComponent() const { return ARPGAbilitySystemComponent; }
	FORCEINLINE UARPGAttributeSet* GetARPGAttributeSet() const { return ARPGAttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UARPGAbilitySystemComponent> ARPGAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UARPGAttributeSet> ARPGAttributeSet;
#pragma endregion

#pragma region Data
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UARPGStartUpDataBase> CharacterStartUpData;
#pragma endregion

#pragma region Combat
public:
	//~ Begin IPawnCombatInterface Interface.
	virtual UARPGPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface
#pragma endregion 

public:
	//~ Begin IPawnUIInterface Interface.
	virtual UARPGPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface

};
