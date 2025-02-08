// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h"
#include <Components/BoxComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Components/DefenceFloatingPawnMovement.h"
#include "Projectile.h"
#include "Tank.generated.h"

UCLASS()
class SHOOTER_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	void Zoom(UINT8 bZoom);
	void Fire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Turret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* TurretSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Socket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ZoomCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDefenceFloatingPawnMovement* DefenceFloatingPawnMovement;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ZoomWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> ProjectileClass;

	UUserWidget* ZoomWidget;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DataTableRowHandle;



};
