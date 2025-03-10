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
    // �������� ���̺� �ε����� ����
    void SetTotalWaveIndex(int32 NewIndex) { TotalWaveIndex = NewIndex; }
    void SetCurrentWaveIndex(int32 NewIndex);

    int32 GetCurrentWaveIndex() const { return CurrentWaveIndex; }

    // AActor �������̽��� ���� ���� ����
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(Replicated)
    int32 TotalWaveIndex;

    UPROPERTY(ReplicatedUsing = OnRep_CurrentWaveIndex, VisibleAnywhere)
    int32 CurrentWaveIndex;


    UFUNCTION()
    void OnRep_CurrentWaveIndex();

};
