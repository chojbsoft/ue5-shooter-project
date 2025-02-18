// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ProjectileEffect.h"

// Sets default values
AProjectileEffect::AProjectileEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	SetRootComponent(AudioComponent);
	ParticleSystemComponent->SetupAttachment(AudioComponent);

}

void AProjectileEffect::SetEffectData(const FEffectDataTableRow* EffectDataTableRow)
{
	const int32 RandomIndex = FMath::RandRange(0, EffectDataTableRow->Sounds.Num() - 1);
	AudioComponent->SetSound(EffectDataTableRow->Sounds[RandomIndex]);
	ParticleSystemComponent->SetTemplate(EffectDataTableRow->ParticleSystem);
}

// Called when the game starts or when spawned
void AProjectileEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

