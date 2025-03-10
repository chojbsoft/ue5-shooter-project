// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DefencePlayerCameraManager.h"
#include "Tank.h"
#include "DefencePlayerController.generated.h"

/**
 *
 */
UCLASS()
class SHOOTER_API ADefencePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefencePlayerController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;


protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnZoomIn(const FInputActionValue& InputActionValue);
	void OnZoomOut(const FInputActionValue& InputActionValue);
	void OnFire(const FInputActionValue& InputActionValue);

public:
	void UpdateWaveUI(int32 CurrentWave, int32 TotalWaves);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WaveInfoWidgetClass;

	UPROPERTY()
	UUserWidget* WaveInfoWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Look;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Zoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* Fire;
};
