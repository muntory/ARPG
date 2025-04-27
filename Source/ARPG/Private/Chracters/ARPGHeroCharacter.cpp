// Fill out your copyright notice in the Description page of Project Settings.


#include "Chracters/ARPGHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/ARPGInputConfigData.h"
#include "Components/Input/ARPGInputComponent.h"
#include "ARPGGameplayTags.h"
#include "Components/Combat/ARPGHeroCombatComponent.h"
#include "AbilitySystem/ARPGAbilitySystemComponent.h"
#include "DataAssets/StartUpData/ARPGHeroStartUpData.h"
#include "Components/UI/ARPGHeroUIComponent.h"
#include "AbilitySystemComponent.h"


#include "ARPGDebugHelper.h"

AARPGHeroCharacter::AARPGHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HeroCombatComponent = CreateDefaultSubobject<UARPGHeroCombatComponent>(TEXT("HeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UARPGHeroUIComponent>(TEXT("HeroUIComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

UARPGPawnUIComponent* AARPGHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UARPGHeroUIComponent* AARPGHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AARPGHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		UARPGStartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous();
		if (LoadedData)
		{
			LoadedData->GiveToAbilitySystemComponent(ARPGAbilitySystemComponent);
		}
	}

	
	GetAbilitySystemComponent()->OnAbilityEnded.AddUObject(this, &ThisClass::ConsumeBuffer);
}

void AARPGHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	checkf(InputConfigData, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigData->DefaultMappingContext, 0);
	UARPGInputComponent* ARPGInputComponent = CastChecked<UARPGInputComponent>(PlayerInputComponent);
	ARPGInputComponent->BindNativeInputAction(InputConfigData, ARPGGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	ARPGInputComponent->BindNativeInputAction(InputConfigData, ARPGGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	ARPGInputComponent->BindAbilityInputAction(InputConfigData, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

UARPGPawnCombatComponent* AARPGHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

void AARPGHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AARPGHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);

	}
}

void AARPGHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	ARPGAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
	
}

void AARPGHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	ARPGAbilitySystemComponent->OnAbilityInputReleased(InInputTag);

}

void AARPGHeroCharacter::ConsumeBuffer(const FAbilityEndedData& Data)
{


	if (InputTagBuffered.IsValid())
	{
		Input_AbilityInputPressed(InputTagBuffered);
		InputTagBuffered = FGameplayTag::EmptyTag;

	}

}

