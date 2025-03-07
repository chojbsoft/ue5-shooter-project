// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/StageSubsystem.h"

void UStageSubsystem::StartStage(UStageDataAsset* InStageDataAsset)
{
	if (!StageDataAsset)
	{
		ensure(false);
		return;
	}

	if (StageDataAsset->Waves.IsEmpty())
	{
		ensure(false);
		return;
	}

	StageDataAsset = InStageDataAsset;
	LevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
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
		return;
	}

	bWaveFinished = false;
	CurrentWaveIndex = WaveIndex;
	FWaveInfo& WaveInfo = StageDataAsset->Waves[WaveIndex];
	LevelSequenceActor->SetSequence(WaveInfo.Wave);
	LevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &UStageSubsystem::OnWaveFinished);

}

void UStageSubsystem::OnWaveFinished()
{
	bWaveFinished = true;
	// 트랜지션 룰이 부합할때만 또 StartWave를 하기 위한 콜백 함수
}
