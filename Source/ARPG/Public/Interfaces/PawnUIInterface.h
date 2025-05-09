// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UARPGPawnUIComponent;
class UARPGHeroUIComponent;
class UARPGEnemyUIComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API IPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UARPGPawnUIComponent* GetPawnUIComponent() const = 0;

	virtual UARPGHeroUIComponent* GetHeroUIComponent() const;

	virtual UARPGEnemyUIComponent* GetEnemyUIComponent() const;
};
