// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FollowPointsAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

void AFollowPointsAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFollowPointsAIController::SetPointsAndMove(const TArray<FVector>& InPoints)
{
    Points = InPoints;
    Move();
}

void AFollowPointsAIController::Move()
{
    if (CurrentPointIndex >= Points.Num())
    {
        return;
    }

    FVector& TargetLocation = Points[CurrentPointIndex++];
    MoveToLocation(TargetLocation);
}

void AFollowPointsAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    if (!Result.IsSuccess())
    {
        ensure(false);
        return;
    }

    Move();
}

