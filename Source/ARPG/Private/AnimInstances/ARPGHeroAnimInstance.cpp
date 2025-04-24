// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/ARPGHeroAnimInstance.h"
#include "Chracters/ARPGHeroCharacter.h"


void UARPGHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroChracter = Cast<AARPGHeroCharacter>(OwningCharacter);
	}
}

void UARPGHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;

		bShouldEnterRelaxState = (EnterRelaxStateThreshold <= IdleElpasedTime);
	}
}
