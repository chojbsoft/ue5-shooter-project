// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatComponent.h"
#include "CombatStatComponent.generated.h"

USTRUCT()
struct SHOOTER_API FCombatStatDataTableRow : public FStatDataTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Attack = 10.0f;

	FCombatStatDataTableRow();
};

UCLASS()
class SHOOTER_API UCombatStatComponent : public UStatComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	float Attack = 10.0f;
};
