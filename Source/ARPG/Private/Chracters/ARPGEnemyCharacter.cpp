// Fill out your copyright notice in the Description page of Project Settings.


#include "Chracters/ARPGEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/ARPGEnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/ARPGEnemyStartUpData.h"
#include "Components/UI/ARPGEnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/ARPGWidgetBase.h"

AARPGEnemyCharacter::AARPGEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UARPGEnemyCombatComponent>("EnemyCombatComponent");

	EnemyUIComponent = CreateDefaultSubobject<UARPGEnemyUIComponent>("EnemyUIComponent");

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());


}

UARPGPawnCombatComponent* AARPGEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UARPGPawnUIComponent* AARPGEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UARPGEnemyUIComponent* AARPGEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AARPGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UARPGWidgetBase* HealthWidget = Cast<UARPGWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AARPGEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AARPGEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UARPGStartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(ARPGAbilitySystemComponent);

				}
			}
		)
	);
}
