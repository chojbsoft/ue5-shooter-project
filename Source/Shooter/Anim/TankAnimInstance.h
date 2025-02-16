// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TankAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UTankAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FRotator TurretRotation;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	APawn* Pawn;
};
