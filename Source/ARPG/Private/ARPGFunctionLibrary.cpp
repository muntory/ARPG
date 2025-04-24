// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"


UARPGAbilitySystemComponent* UARPGFunctionLibrary::NativeGetARPGASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UARPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UARPGFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UARPGAbilitySystemComponent* ASC = NativeGetARPGASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UARPGFunctionLibrary::RemoveGameplayTagToActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UARPGAbilitySystemComponent* ASC = NativeGetARPGASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UARPGFunctionLibrary::NativeActorHasSpecificTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UARPGAbilitySystemComponent* ASC = NativeGetARPGASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UARPGFunctionLibrary::BP_ActorHasSpecificTag(AActor* InActor, FGameplayTag TagToCheck, EARPGConfirmType& OutConfirmType)
{
	OutConfirmType = NativeActorHasSpecificTag(InActor, TagToCheck) ? EARPGConfirmType::Yes : EARPGConfirmType::No;
}

UARPGPawnCombatComponent* UARPGFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UARPGPawnCombatComponent* UARPGFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EARPGValidType& OutValidType)
{
	UARPGPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EARPGValidType::Valid : EARPGValidType::Invalid;

	return CombatComponent;
}
