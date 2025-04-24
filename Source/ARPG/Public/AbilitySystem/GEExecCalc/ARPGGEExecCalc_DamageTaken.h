// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ARPGGEExecCalc_DamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UARPGGEExecCalc_DamageTaken();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
