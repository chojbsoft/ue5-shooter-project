// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Effect.generated.h"

USTRUCT()
struct FEffectDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Sounds;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
};

UCLASS()
class SHOOTER_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffect();
	void SetData(const FEffectDataTableRow* EffectDataTableRow);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
};
