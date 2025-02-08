// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DefenceFloatingPawnMovement.h"


void UDefenceFloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccelerationVector = Velocity.GetSafeNormal();

	// PhysicsRotation 부분 복붙
	FRotator CurrentRotation = UpdatedComponent->GetComponentRotation(); // Normalized
	CurrentRotation.DiagnosticCheckNaN(TEXT("UDefenceFloatingPawnMovement::TickComponent(): CurrentRotation"));

	const float DeltaTimeOverride = DeltaTime * RotationSpeedRate;

	FRotator DeltaRot = GetDeltaRotation(DeltaTimeOverride);
	DeltaRot.DiagnosticCheckNaN(TEXT("UDefenceFloatingPawnMovement::TickComponent(): CurrentRotation"));

	FRotator DesiredRotation = CurrentRotation;
	DesiredRotation = ComputeOrientToMovementRotation(CurrentRotation, DeltaTime, DeltaRot);

	// Accumulate a desired new rotation.
	const float AngleTolerance = 1e-3f;

	if (!CurrentRotation.Equals(DesiredRotation, AngleTolerance))
	{
		// If we'd be prevented from becoming vertical, override the non-yaw rotation rates to allow the character to snap upright
		if (FMath::IsNearlyZero(DeltaRot.Pitch))
		{
			DeltaRot.Pitch = 360.0;
		}
		if (FMath::IsNearlyZero(DeltaRot.Roll))
		{
			DeltaRot.Roll = 360.0;
		}
	}

	// PITCH
	if (!FMath::IsNearlyEqual(CurrentRotation.Pitch, DesiredRotation.Pitch, AngleTolerance))
	{
		DesiredRotation.Pitch = FMath::FixedTurn(CurrentRotation.Pitch, DesiredRotation.Pitch, DeltaRot.Pitch);
	}

	// YAW
	if (!FMath::IsNearlyEqual(CurrentRotation.Yaw, DesiredRotation.Yaw, AngleTolerance))
	{
		DesiredRotation.Yaw = FMath::FixedTurn(CurrentRotation.Yaw, DesiredRotation.Yaw, DeltaRot.Yaw);
	}

	// ROLL
	if (!FMath::IsNearlyEqual(CurrentRotation.Roll, DesiredRotation.Roll, AngleTolerance))
	{
		DesiredRotation.Roll = FMath::FixedTurn(CurrentRotation.Roll, DesiredRotation.Roll, DeltaRot.Roll);
	}

	// Set the new rotation.
	DesiredRotation.DiagnosticCheckNaN(TEXT("UDefenceFloatingPawnMovement::TickComponent(): CurrentRotation"));
	MoveUpdatedComponent(FVector::ZeroVector, DesiredRotation, /*bSweep*/ false);
}

FRotator UDefenceFloatingPawnMovement::GetDeltaRotation(float DeltaTime) const
{
	return FRotator(GetAxisDeltaRotation(RotationRate.Pitch, DeltaTime), GetAxisDeltaRotation(RotationRate.Yaw, DeltaTime), GetAxisDeltaRotation(RotationRate.Roll, DeltaTime));
}

float UDefenceFloatingPawnMovement::GetAxisDeltaRotation(float InAxisRotationRate, float DeltaTime) const
{
	// Values over 360 don't do anything, see FMath::FixedTurn. However we are trying to avoid giant floats from overflowing other calculations.
	return (InAxisRotationRate >= 0.f) ? FMath::Min(InAxisRotationRate * DeltaTime, 360.f) : 360.f;
}

FRotator UDefenceFloatingPawnMovement::ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const
{
	if (AccelerationVector.SizeSquared() < UE_KINDA_SMALL_NUMBER)
	{
		// Don't change rotation if there is no AccelerationVector.
		return CurrentRotation;
	}

	// Rotate toward direction of AccelerationVector.
	return AccelerationVector.GetSafeNormal().Rotation();
}
