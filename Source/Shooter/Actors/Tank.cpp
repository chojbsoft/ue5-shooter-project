// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	TurretSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("TurretSpringArmComponent"));
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Socket = CreateDefaultSubobject<USceneComponent>(TEXT("Socket"));
	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));

	DefenceFloatingPawnMovement = CreateDefaultSubobject<UDefenceFloatingPawnMovement>(TEXT("MovementComponent"));

	SetRootComponent(BoxComponent);
	SpringArmComponent->SetupAttachment(BoxComponent);
	MainCamera->SetupAttachment(SpringArmComponent);

	Body->SetupAttachment(RootComponent);
	TurretSpringArmComponent->SetupAttachment(RootComponent);
	Turret->SetupAttachment(TurretSpringArmComponent);
	Socket->SetupAttachment(Turret);
	ZoomCamera->SetupAttachment(Socket);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	ZoomWidget = CreateWidget(GetWorld(), ZoomWidgetClass);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Zoom(UINT8 bZoom)
{
	if (bZoom)
	{
		ZoomWidget->AddToViewport(0);
		ZoomCamera->SetActive(true);
		MainCamera->SetActive(false);
	}
	else
	{
		ZoomCamera->SetActive(false);
		MainCamera->SetActive(true);
		ZoomWidget->RemoveFromParent();
	}
}

void ATank::Fire()
{
	FTransform Transform = FTransform(Socket->GetComponentRotation(), Socket->GetComponentLocation(), FVector::One());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, Transform, this, this
		, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->SetData(DataTableRowHandle);
	//Projectile->GetProjectileMovementComponent()->InitialSpeed = 2000.f;
	//Projectile->GetProjectileMovementComponent()->MaxSpeed = 2000.f;
	Projectile->FinishSpawning(Transform, true);
}

