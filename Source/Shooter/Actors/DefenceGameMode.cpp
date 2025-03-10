// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DefenceGameMode.h"

#include <Kismet/GameplayStatics.h>
#include "Actors/Enemy.h"
#include "Actors/SplineEnemySpawner.h"

ADefenceGameMode::ADefenceGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartStage();
}

void ADefenceGameMode::StartStage()
{
	if (!StageDataAsset || StageDataAsset->Waves.IsEmpty())
	{
		SetActorTickEnabled(false);
		return;
	}
	if (IsValid(LevelSequenceActor))
	{
		LevelSequenceActor->Destroy();
		ensure(false);
	}

	LevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	StartWave(0);
}

void ADefenceGameMode::StartWave(const uint32 WaveIndex)
{
	if (WaveIndex >= (uint32)StageDataAsset->Waves.Num())
	{
		OnStageFinished();
		return;
	}

	bWaveFinished = false;
	CurrentWaveIndex = WaveIndex;
	FWaveInfo& WaveInfo = StageDataAsset->Waves[WaveIndex];
	LevelSequenceActor->SetSequence(WaveInfo.Wave);
	if (!LevelSequenceActor->GetSequencePlayer()->OnFinished.IsBound())
	{
		LevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &ADefenceGameMode::OnWaveFinished);
	}
	LevelSequenceActor->GetSequencePlayer()->Play();
}

void ADefenceGameMode::OnStageFinished()
{
	LevelSequenceActor->Destroy();
	StageDataAsset = nullptr;
}

void ADefenceGameMode::OnWaveFinished()
{
	bWaveFinished = true;
}

void ADefenceGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CanTransitionWave())
	{
		return;
	}

	const uint32 NextWaveIndex = CurrentWaveIndex + 1;
	StartWave(NextWaveIndex);
}

bool ADefenceGameMode::CanTransitionWave()
{
	if (!bWaveFinished)
	{
		return false;
	}

	FWaveTransitionRule WaveTransitionRule = StageDataAsset->Waves[CurrentWaveIndex].WaveTransitionRule;
	switch (WaveTransitionRule)
	{
	case FWaveTransitionRule::Auto:
		return true;
	case FWaveTransitionRule::KillAllEnemies:
	{
		AActor* FindSpawner = UGameplayStatics::GetActorOfClass(LevelSequenceActor, ASplineEnemySpawner::StaticClass());
		if (FindSpawner)
		{
			return false;
		}
		AActor* FindEnemy = UGameplayStatics::GetActorOfClass(LevelSequenceActor, AEnemy::StaticClass());
		if (FindEnemy)
		{
			return false;
		}
	}
	return true;
	}

	return false;
}
