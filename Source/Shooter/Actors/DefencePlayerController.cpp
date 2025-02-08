// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DefencePlayerController.h"

ADefencePlayerController::ADefencePlayerController()
{
	PlayerCameraManagerClass = ADefencePlayerCameraManager::StaticClass();
}

void ADefencePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADefencePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// DefaultInput.ini 파일보면 현재 InputComponent는 EnhancedInputComponent 사용 중
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(Look, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	EnhancedInputComponent->BindAction(Zoom, ETriggerEvent::Started, this, &ThisClass::OnZoomIn);
	EnhancedInputComponent->BindAction(Zoom, ETriggerEvent::Completed, this, &ThisClass::OnZoomOut);
	EnhancedInputComponent->BindAction(Fire, ETriggerEvent::Triggered, this, &ThisClass::OnFire);
}

void ADefencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// IMC 여러개를 추가 할 수 있는데, 여기서 우선순위 정할 수 있음
	// 입력 소진을 활성화하면, 우선 순위가 높은 입력만 처리됨
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

void ADefencePlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	const FRotator Rotator = AActor::GetActorRotation();
	const FRotator YawRotator = FRotator(0.0, Rotator.Yaw, 0.0);
	const FVector ForwardVector = YawRotator.Vector();
	const FVector RightVector = UKismetMathLibrary::GetRightVector(Rotator);

	APawn* ControlledPawn = GetPawn();
	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);
}

void ADefencePlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void ADefencePlayerController::OnZoomIn(const FInputActionValue& InputActionValue)
{
	Cast<ATank>(GetPawn())->Zoom(true);
}

void ADefencePlayerController::OnZoomOut(const FInputActionValue& InputActionValue)
{
	Cast<ATank>(GetPawn())->Zoom(false);
}

void ADefencePlayerController::OnFire(const FInputActionValue& InputActionValue)
{
	Cast<ATank>(GetPawn())->Fire();
}
