// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefenceAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UDefenceAnimInstance : public UAnimInstance
{
	GENERATED_BODY()



protected:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
    float Speed;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
    bool bShouldMove;

private:
    APawn* OwningPawn;
};
