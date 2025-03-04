// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Components/SkeletalMeshComponent.h>
#include <Components/BoxComponent.h>
#include "Components/DefenceFloatingPawnMovement.h"
#include "Components/StatComponent.h"
#include <Components/TimelineComponent.h>
#include "FollowPointsAIController.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTER_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

protected:
	UFUNCTION()
	void OnTimelineFloat(float Value);

	UFUNCTION()
	void OnTimelineFinished();


protected:
	// Components
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	UDefenceFloatingPawnMovement* DefenceFloatingPawnMovement;

	UPROPERTY(EditAnywhere)
	UStatComponent* StatComponent;

protected:
	// Stat DT
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle StatDataTableRowHandle;

protected:
	// Destroy
	UPROPERTY(EditAnywhere)
	UTimelineComponent* TimelineComponent;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIController> MyAIControllerClass;
};
