// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/ARPGInputConfigData.h"
#include "ARPGInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<typename UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UARPGInputConfigData* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<typename UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UARPGInputConfigData* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template<typename UserObject, typename CallbackFunc>
inline void UARPGInputComponent::BindNativeInputAction(const UARPGInputConfigData* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<typename UserObject, typename CallbackFunc>
inline void UARPGInputComponent::BindAbilityInputAction(const UARPGInputConfigData* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	for (const FARPGInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);

	}
}
