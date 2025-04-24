// Fill out your copyright notice in the Description page of Project Settings.


#include "Chracters/ARPGBaseCharacter.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "AbilitySystem/ARPGAttributeSet.h"
#include "DataAssets/StartUpData/ARPGStartUpDataBase.h"

// Sets default values
AARPGBaseCharacter::AARPGBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	ARPGAbilitySystemComponent = CreateDefaultSubobject<UARPGAbilitySystemComponent>(TEXT("ARPGAbilitySystemComponent"));
	ARPGAttributeSet = CreateDefaultSubobject<UARPGAttributeSet>(TEXT("ARPGAttributeSet"));
}

void AARPGBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ARPGAbilitySystemComponent)
	{
		ARPGAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}

	
}

UAbilitySystemComponent* AARPGBaseCharacter::GetAbilitySystemComponent() const
{
	return GetARPGAbilitySystemComponent();
}

UARPGPawnCombatComponent* AARPGBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UARPGPawnUIComponent* AARPGBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}


