// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

USTRUCT()
struct SHOOTER_API FStatDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	FStatDataTableRow();

	UPROPERTY(EditAnywhere)
	float HP = 10;
	
	TSubclassOf<class UStatComponent> StatComponentClass;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual float ProcessDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	virtual void SetData(FStatDataTableRow* StatDataTableRow);

public:
	float GetHP() { return HP; }

protected:
	UPROPERTY(EditAnywhere)
	float HP = 10;
		
};
