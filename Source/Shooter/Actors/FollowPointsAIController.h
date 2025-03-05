// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "FollowPointsAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AFollowPointsAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void SetPointsAndMove(const TArray<FVector>& InPoints);

public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	void Move();

protected:
	TArray<FVector> Points;
	int32 CurrentPointIndex = 0;
};
