// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/SplineComponent.h>


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineEnemySpawner.generated.h"

USTRUCT()
struct FEnemySpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SpawnDelay = 1.f;

	UPROPERTY(EditAnywhere)
	int32 SpawnCount = 1;

	UPROPERTY(EditAnywhere)
	UClass* EnemyClass;
};

UCLASS()
class UEnemySpawnDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FEnemySpawnInfo> EnemySpawnInfoArray;
};

UCLASS()
class SHOOTER_API ASplineEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void StartWave();

protected:

	UFUNCTION()
	void Spawn(FEnemySpawnInfo& InEnemySpawnInfo, const uint32 InRemainCount);

protected:
	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UEnemySpawnDataAsset* EnemySpawnDataAsset;
	int32 CurrentSpawnIndex = 0;

	FTimerHandle TimerHandle;
};
