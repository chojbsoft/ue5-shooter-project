// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SkeletalTank.h"
#include "Actors/Effect.h"

// Sets default values
ASkeletalTank::ASkeletalTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	DefenceFloatingPawnMovement = CreateDefaultSubobject<UDefenceFloatingPawnMovement>(TEXT("MovementComponent"));
	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));

	SetRootComponent(BoxComponent);
	SpringArmComponent->SetupAttachment(BoxComponent);
	MainCamera->SetupAttachment(SpringArmComponent);
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	ZoomCamera->SetupAttachment(SkeletalMeshComponent, TEXT("ZoomCameraSocket"));

	BoxComponent->SetCollisionProfileName(TEXT("Player"));
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritRoll = false;

	const TSet<UActorComponent*>& Components = GetComponents();
	for (UActorComponent* Component : Components)
	{
		if (Component != SkeletalMeshComponent)
		{
			SkeletalMeshComponent->AddTickPrerequisiteComponent(Component);
		}
	}



}

// Called when the game starts or when spawned
void ASkeletalTank::BeginPlay()
{
	Super::BeginPlay();
	ZoomWidget = CreateWidget(GetWorld(), ZoomWidgetClass);

}

void ASkeletalTank::OnConstruction(const FTransform& Transform)
{
	if (!DataTableRowHandle.DataTable) { return; }
	if (DataTableRowHandle.IsNull()) { return; }
	ProjectileTableRow = DataTableRowHandle.GetRow<FProjectileDataTableRow>(TEXT("TankProjectile"));

	UMaterialInterface* Material = SkeletalMeshComponent->GetMaterial(1);
	if (Material)
	{
		MID = UMaterialInstanceDynamic::Create(Material, SkeletalMeshComponent);
		SkeletalMeshComponent->SetMaterial(1, MID);
	}
}

// Called every frame
void ASkeletalTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkeletalTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ASkeletalTank::Zoom(UINT8 bZoom)
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

void ASkeletalTank::Fire()
{
	if (!ProjectileTableRow)
	{
		return;
	}

	bool bTimer = GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle);
	if (bTimer) { return; }
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, ProjectileTableRow->FireDelay, false);

	FRotator ZoomRotator = ZoomCamera->GetComponentRotation();
	FTransform Transform = FTransform(FRotator(0., ZoomRotator.Yaw, 0.), ZoomCamera->GetComponentLocation(), FVector::One());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, Transform, this, this
		, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->SetData(ProjectileTableRow);
	Projectile->FinishSpawning(Transform, true);

	if (!ProjectileTableRow->FireEffect.DataTable || ProjectileTableRow->FireEffect.RowName.IsNone())
	{
		return;
	}

	AEffect* Effect = GetWorld()->SpawnActorDeferred<AEffect>(AEffect::StaticClass()
		, ZoomCamera->GetComponentTransform(), this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Effect->SetData(ProjectileTableRow->FireEffect.GetRow<FEffectDataTableRow>(TEXT("ProjectileEffect")));
	Effect->FinishSpawning(ZoomCamera->GetComponentTransform());
}

