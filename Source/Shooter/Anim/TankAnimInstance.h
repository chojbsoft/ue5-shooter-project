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
	FRotator TurretRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly)
	float TurretRotationSpeed = 1.0f;

	UPROPERTY()
	APawn* Pawn = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FRotator WheelRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly)
	double Track = 0.0;
	
};
