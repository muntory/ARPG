// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "ARPGTypes/ARPGEnumTypes.h"
#include "ARPGFunctionLibrary.generated.h"

class UARPGAbilitySystemComponent;
class UARPGPawnCombatComponent;


/**
 * 
 */
UCLASS()
class ARPG_API UARPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UARPGAbilitySystemComponent* NativeGetARPGASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary")
	static void RemoveGameplayTagToActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeActorHasSpecificTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary", meta = (DisplayName = "Actor Has Specific Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_ActorHasSpecificTag(AActor* InActor, FGameplayTag TagToCheck, EARPGConfirmType& OutConfirmType);

	static UARPGPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "ARPG|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UARPGPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor * InActor, EARPGValidType & OutValidType);
};
