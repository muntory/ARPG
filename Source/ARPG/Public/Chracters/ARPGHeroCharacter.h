// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chracters/ARPGBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "ARPGHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UARPGInputConfigData;
struct FInputActionValue;
class UARPGHeroCombatComponent;
class UARPGHeroUIComponent;
struct FAbilityEndedData;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGHeroCharacter : public AARPGBaseCharacter
{
	GENERATED_BODY()

public:
	AARPGHeroCharacter();

	//~ Begin IPawnUIInterface Interface.
	virtual UARPGPawnUIComponent* GetPawnUIComponent() const override;
	virtual UARPGHeroUIComponent* GetHeroUIComponent() const override;

	//~ End IPawnUIInterface Interface
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Components
public:
	FORCEINLINE UARPGHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UARPGHeroCombatComponent> HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UARPGHeroUIComponent> HeroUIComponent;

public:
	//~ Begin IPawnCombatInterface Interface.
	virtual UARPGPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

#pragma endregion

#pragma region Inputs
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UARPGInputConfigData> InputConfigData;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

	UFUNCTION()
	void ConsumeBuffer(const FAbilityEndedData& Data);

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FGameplayTag InputTagBuffered;

#pragma endregion


};
