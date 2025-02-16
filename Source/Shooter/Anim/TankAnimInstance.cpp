// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/TankAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

void UTankAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Pawn = TryGetPawnOwner();
	if (!Pawn)
	{
		return;
	}

	TurretRotation = Pawn->GetControlRotation();
}

void UTankAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Pawn)
	{
		return;
	}

	FRotator Rotator = Pawn->GetControlRotation();
	TurretRotation = UKismetMathLibrary::RLerp(FRotator(0., TurretRotation.Yaw, 0.), Rotator, DeltaSeconds * Speed, true);
}
