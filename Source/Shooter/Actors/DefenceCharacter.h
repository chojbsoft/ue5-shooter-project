// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Projectile.h"
#include "Interface/ShooterInterface.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/ArrowComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefenceCharacter.generated.h"

UCLASS()
class SHOOTER_API ADefenceCharacter : public ACharacter, public IShooterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefenceCharacter();

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

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveZoom(uint8 bZoom);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WeaponComponent;

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle ProjectileTableRowHandle;

	FProjectileDataTableRow* ProjectileTableRow;

	UPROPERTY()
	UMaterialInstanceDynamic* MID;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> ProjectileClass;

	FTimerHandle FireTimerHandle;
};
