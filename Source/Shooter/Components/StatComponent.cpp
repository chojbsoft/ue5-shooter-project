// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatComponent.h"

FStatDataTableRow::FStatDataTableRow()
{
	StatComponentClass = UStatComponent::StaticClass();
}

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UStatComponent::ProcessDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HP -= DamageAmount;
	if (HP <= 0.f)
	{
		AActor* Actor = GetOwner();
		Actor->Destroy();
	}
	return HP;
}

void UStatComponent::SetData(FStatDataTableRow* StatDataTableRow)
{
	HP = StatDataTableRow->HP;
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

