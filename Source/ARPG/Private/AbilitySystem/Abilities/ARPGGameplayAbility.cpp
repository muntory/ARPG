// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ARPGGameplayAbility.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Components/Combat/ARPGPawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


void UARPGGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EARPGAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UARPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EARPGAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UARPGPawnCombatComponent* UARPGGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetOwningActorFromActorInfo()->FindComponentByClass<UARPGPawnCombatComponent>();
}

UARPGAbilitySystemComponent* UARPGGameplayAbility::GetARPGAbilitySystemComponentFromActorInfo() const
{
	return Cast<UARPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UARPGGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetARPGAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC

	);
}

FActiveGameplayEffectHandle UARPGGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EARPGSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EARPGSuccessType::Successful : EARPGSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

