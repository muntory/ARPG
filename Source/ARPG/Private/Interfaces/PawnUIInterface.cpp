// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UARPGHeroUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
	return nullptr;
}

UARPGEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
