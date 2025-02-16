// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include <Components/BoxComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Components/DefenceFloatingPawnMovement.h"
#include "Projectile.h"
#include "Interface/TankInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SkeletalTank.generated.h"

UCLASS()
class SHOOTER_API ASkeletalTank : public APawn, public ITankInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkeletalTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Zoom(UINT8 bZoom) override;
	virtual void Fire() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ZoomCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDefenceFloatingPawnMovement* DefenceFloatingPawnMovement;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ZoomWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY()
	UUserWidget* ZoomWidget;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;

	FProjectileTableRow* ProjectileTableRow;

	UPROPERTY()
	FTimerHandle FireTimerHandle;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EffectClass;

};
