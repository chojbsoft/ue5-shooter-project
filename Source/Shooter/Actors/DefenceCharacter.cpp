// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DefenceCharacter.h"

// Sets default values
ADefenceCharacter::ADefenceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefenceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefenceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

