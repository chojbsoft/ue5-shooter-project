// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};
