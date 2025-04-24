// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chracters/ARPGBaseCharacter.h"
#include "ARPGEnemyCharacter.generated.h"

class UARPGEnemyCombatComponent;
class UARPGEnemyUIComponent;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class ARPG_API AARPGEnemyCharacter : public AARPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	AARPGEnemyCharacter();

	//~ Begin IPawnCombatInterface Interface.
	virtual UARPGPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface.
	virtual UARPGPawnUIComponent* GetPawnUIComponent() const override;
	virtual UARPGEnemyUIComponent* GetEnemyUIComponent() const override;

	//~ End IPawnUIInterface Interface

protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

private:
	void InitEnemyStartUpData();
public:
	FORCEINLINE UARPGEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UARPGEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UARPGEnemyUIComponent> EnemyUIComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;
};
