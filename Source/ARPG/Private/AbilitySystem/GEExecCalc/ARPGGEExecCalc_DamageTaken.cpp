// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/ARPGGEExecCalc_DamageTaken.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "ARPGGameplayTags.h"

#include "ARPGDebugHelper.h"
struct FARPGDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)


	FARPGDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UARPGAttributeSet, DamageTaken, Target, false)


	}
};

static const FARPGDamageCapture& GetARPGDamageCapture()
{
	static FARPGDamageCapture ARPGDamageCapture;
	return ARPGDamageCapture;
}

UARPGGEExecCalc_DamageTaken::UARPGGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetARPGDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetARPGDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetARPGDamageCapture().DamageTakenDef);

}

void UARPGGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetARPGDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	// Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(ARPGGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			// Debug::Print(TEXT("BaseDamage"), BaseDamage);

		}

		if (TagMagnitude.Key.MatchesTagExact(ARPGGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);

		}

		if (TagMagnitude.Key.MatchesTagExact(ARPGGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);

		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetARPGDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	// Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
		// Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);

	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;

		BaseDamage *= DamageIncreasePercentHeavy;
		// Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);

	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	// Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetARPGDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
