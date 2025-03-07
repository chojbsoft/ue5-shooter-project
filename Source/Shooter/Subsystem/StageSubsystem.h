// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "StageSubsystem.generated.h"

UENUM(BlueprintType)
enum class FWaveTransitionRule : uint8
{
	Auto,
	KillAllEnemies
};

USTRUCT()
struct FWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ULevelSequence* Wave;

	// 전환 조건
	UPROPERTY(EditAnywhere)
	FWaveTransitionRule WaveTransitionRule = FWaveTransitionRule::Auto;
};

UCLASS(BlueprintType)
class UStageDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FWaveInfo> Waves;
};

UCLASS()
class SHOOTER_API UStageSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartStage(UStageDataAsset* InStageDataAsset);
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

protected:
	void StartWave(const uint32 WaveIndex);

	UFUNCTION()
	void OnWaveFinished();

protected:
	UPROPERTY(Transient)
	UStageDataAsset* StageDataAsset;
	UPROPERTY(Transient)
	ALevelSequenceActor* LevelSequenceActor;

	bool bWaveFinished = false;
	uint32 CurrentWaveIndex = 0;
};
