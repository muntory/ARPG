// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ARPGBaseAnimInstance.h"
#include "ARPGCharacterAnimInstance.generated.h"

class AARPGBaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class ARPG_API UARPGCharacterAnimInstance : public UARPGBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<AARPGBaseCharacter> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
