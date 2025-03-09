// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/DefenceAnimInstance.h"

void UDefenceAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    OwningPawn = TryGetPawnOwner();
}

void UDefenceAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (OwningPawn)
    {
        FVector Velocity = OwningPawn->GetVelocity();
        Speed = Velocity.Size2D();
        bShouldMove = Speed >= 5.0f;

        const FRotator& Rotator = OwningPawn->GetActorRotation();
        Direction = CalculateDirection(Velocity, Rotator);

        PitchRotator = FRotator(0.0, 0.0, OwningPawn->GetBaseAimRotation().Pitch / -5.0);
    }
}
