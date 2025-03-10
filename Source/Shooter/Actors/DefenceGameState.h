// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DefenceGameState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ADefenceGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
    ADefenceGameState();

public:
    // 서버에서 웨이브 인덱스를 설정
    void SetTotalWaveIndex(int32 NewIndex) { TotalWaveIndex = NewIndex; }
    void SetCurrentWaveIndex(int32 NewIndex);

    int32 GetCurrentWaveIndex() const { return CurrentWaveIndex; }

    // AActor 인터페이스를 통해 복제 설정
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(Replicated)
    int32 TotalWaveIndex;

    UPROPERTY(ReplicatedUsing = OnRep_CurrentWaveIndex, VisibleAnywhere)
    int32 CurrentWaveIndex;


    UFUNCTION()
    void OnRep_CurrentWaveIndex();

};
