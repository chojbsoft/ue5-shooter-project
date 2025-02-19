// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Actors/Effect.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.f;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	SetRootComponent(Collider);
	StaticMeshComponent->SetupAttachment(Collider);

	OnActorHit.AddDynamic(this, &AProjectile::OnActorHitFunction);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::SetData(const FProjectileDataTableRow* Row)
{
	ProjectileMovementComponent->InitialSpeed = Row->ProjectileSpeed;
	InitialLifeSpan = Row->InitialLifeSpan;

	if (!Row->Materials.IsEmpty())
	{
		const int32 Num = StaticMeshComponent->GetStaticMesh()->GetStaticMaterials().Num();
		if (Row->Materials.Num() != Num)
		{
			ensure(false);
		}
		else
		{
			for (uint32 i=0; UMaterial* It : Row->Materials)
			{
				StaticMeshComponent->SetMaterial(i++, It);
			}
		}
	}
}

void AProjectile::OnActorHitFunction(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!DataTableRowHandle.DataTable || DataTableRowHandle.RowName.IsNone())
	{
		return;
	}

	const FTransform& Transform = SelfActor->GetActorTransform();
	AEffect* Effect = GetWorld()->SpawnActorDeferred<AEffect>(AEffect::StaticClass(), Transform
		, this, this->GetInstigator(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FEffectDataTableRow* Row = DataTableRowHandle.GetRow<FEffectDataTableRow>(TEXT("HitEffect"));
	if (!Row)
	{
		return;
	}
	Effect->SetData(Row);

	Effect->FinishSpawning(Transform);
}

