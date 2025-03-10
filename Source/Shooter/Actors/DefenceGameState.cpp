// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DefenceGameState.h"
#include "Net/UnrealNetwork.h"
#include "DefencePlayerController.h"

ADefenceGameState::ADefenceGameState()
{
    CurrentWaveIndex = 0;
}

void ADefenceGameState::SetCurrentWaveIndex(int32 NewIndex)
{
    if (HasAuthority())
    {
        CurrentWaveIndex = NewIndex;
        OnRep_CurrentWaveIndex();
    }
}

void ADefenceGameState::OnRep_CurrentWaveIndex()
{
     for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (PC && PC->IsLocalController())
        {
            ADefencePlayerController* MyPC = Cast<ADefencePlayerController>(PC);
            if (MyPC)
            {
                MyPC->UpdateWaveUI(CurrentWaveIndex + 1, TotalWaveIndex);
            }
        }
    }
}

void ADefenceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ADefenceGameState, TotalWaveIndex);
    DOREPLIFETIME(ADefenceGameState, CurrentWaveIndex);
}