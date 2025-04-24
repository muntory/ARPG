// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/ARPGInputConfigData.h"

UInputAction* UARPGInputConfigData::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FARPGInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputAction && InputActionConfig.InputTag == InInputTag)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
