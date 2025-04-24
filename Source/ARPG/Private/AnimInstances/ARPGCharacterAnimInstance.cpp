// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ARPGCharacterAnimInstance.h"
#include "Chracters/ARPGBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UARPGCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AARPGBaseCharacter>(TryGetPawnOwner());
	ensure(OwningCharacter);

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UARPGCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningMovementComponent->Velocity.Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

}

