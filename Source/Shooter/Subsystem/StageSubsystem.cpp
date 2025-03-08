// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/StageSubsystem.h"
#include <Kismet/GameplayStatics.h>
#include "Actors/Enemy.h"
#include "Actors/SplineEnemySpawner.h"

void UStageSubsystem::StartStage(UStageDataAsset* InStageDataAsset)
{
	if (!InStageDataAsset)
	{
		ensure(false);
		return;
	}

	if (InStageDataAsset->Waves.IsEmpty())
	{
		ensure(false);
		return;
	}

	if (IsValid(LevelSequenceActor))
	{
		LevelSequenceActor->Destroy();
		ensure(false);
	}

	StageDataAsset = InStageDataAsset;
	LevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	StartWave(0);
}

void UStageSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(StageDataAsset))
	{
		return;
	}
	if (!IsValid(LevelSequenceActor))
	{
		return;
	}
	if (!CanTransitionWave()) { return; }

	const uint32 NextWaveIndex = CurrentWaveIndex + 1;
	StartWave(NextWaveIndex);
}

TStatId UStageSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UStageSubsystem, STATGROUP_Tickables);
}

void UStageSubsystem::StartWave(const uint32 WaveIndex)
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
		LevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &UStageSubsystem::OnWaveFinished);
	}
	LevelSequenceActor->GetSequencePlayer()->Play();

}

bool UStageSubsystem::CanTransitionWave()
{
	if (!bWaveFinished) { return false; }

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

void UStageSubsystem::OnWaveFinished()
{
	bWaveFinished = true;
	// 트랜지션 룰이 부합할때만 또 StartWave를 하기 위한 콜백 함수
}

void UStageSubsystem::OnStageFinished()
{
	LevelSequenceActor->Destroy();
	StageDataAsset = nullptr;
}
