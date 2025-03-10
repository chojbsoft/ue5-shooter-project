// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefenceGameMode.generated.h"

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
class SHOOTER_API ADefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADefenceGameMode();
	virtual void BeginPlay() override;

private:
	void StartStage();
	void StartWave(const uint32 WaveIndex);

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	bool CanTransitionWave();

	UFUNCTION()
	void OnWaveFinished();
	void OnStageFinished();

protected:
	UPROPERTY(EditAnywhere)
	UStageDataAsset* StageDataAsset;
	UPROPERTY(Transient)
	ALevelSequenceActor* LevelSequenceActor;

	bool bWaveFinished = false;
	uint32 CurrentWaveIndex = 0;
};
