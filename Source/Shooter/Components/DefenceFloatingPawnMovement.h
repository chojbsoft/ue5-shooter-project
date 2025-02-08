// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "DefenceFloatingPawnMovement.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class SHOOTER_API UDefenceFloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FRotator GetDeltaRotation(float DeltaTime) const;
	float GetAxisDeltaRotation(float InAxisRotationRate, float InDeltaTime) const;
	FRotator ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const;

protected:
	FRotator RotationRate = FRotator(0.f, 360.f, 0.f);

	UPROPERTY()
	FVector AccelerationVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeedRate = 1.;

};
