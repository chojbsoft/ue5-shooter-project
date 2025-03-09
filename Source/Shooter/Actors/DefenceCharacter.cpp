// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DefenceCharacter.h"
#include "Effect.h"

// Sets default values
ADefenceCharacter::ADefenceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CameraBoom (스프링암) 생성 및 루트 컴포넌트에 부착
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;                
	CameraBoom->bUsePawnControlRotation = true;          

	// FollowCamera 생성 및 스프링암 끝에 부착
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;        

	WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(GetMesh(), FName(TEXT("hand_rSocket")));
}

// Called when the game starts or when spawned
void ADefenceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefenceCharacter::OnConstruction(const FTransform& Transform)
{
	if (!ProjectileTableRowHandle.DataTable) { return; }
	if (ProjectileTableRowHandle.IsNull()) { return; }
	ProjectileTableRow = ProjectileTableRowHandle.GetRow<FProjectileDataTableRow>(ProjectileTableRowHandle.RowName.ToString());

	int i = 0;
	for (auto Material : GetMesh()->GetMaterials())
	{
		MID = UMaterialInstanceDynamic::Create(Material, GetMesh());
		GetMesh()->SetMaterial(i++, MID);
	}
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

void ADefenceCharacter::Zoom(UINT8 bZoom)
{
	ReceiveZoom(bZoom);
}

void ADefenceCharacter::Fire()
{
	if (!ProjectileTableRow)
	{
		return;
	}

	bool bTimer = GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle);
	if (bTimer) { return; }
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, ProjectileTableRow->FireDelay, false);


	const FTransform SocketTransform = WeaponComponent->GetSocketTransform(FName(TEXT("FireSocket")));
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SocketTransform, this, this
		, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->SetData(ProjectileTableRow);
	Projectile->FinishSpawning(SocketTransform, true);

	if (!ProjectileTableRow->FireEffect.DataTable || ProjectileTableRow->FireEffect.RowName.IsNone())
	{
		return;
	}

	AEffect* Effect = GetWorld()->SpawnActorDeferred<AEffect>(AEffect::StaticClass()
		, FollowCamera->GetComponentTransform(), this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Effect->SetData(ProjectileTableRow->FireEffect.GetRow<FEffectDataTableRow>(TEXT("ProjectileEffect")));
	Effect->FinishSpawning(FollowCamera->GetComponentTransform());
}

