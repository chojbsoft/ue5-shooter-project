// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	DefenceFloatingPawnMovement = CreateDefaultSubobject<UDefenceFloatingPawnMovement>(TEXT("DefenceFloatingPawnMovement"));
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));

	SetRootComponent(BoxComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionProfileName(TEXT("Enemy"));
	BoxComponent->SetCanEverAffectNavigation(false);

	// Timeline
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
	AIControllerClass = MyAIControllerClass;

	if (StatDataTableRowHandle.DataTable && StatDataTableRowHandle.RowName != NAME_None)
	{
		FStatDataTableRow* StatDataTableRow = StatDataTableRowHandle.GetRow<FStatDataTableRow>(StatDataTableRowHandle.RowName.ToString());
		StatComponent = NewObject<UStatComponent>(this, StatDataTableRow->StatComponentClass);
		StatComponent->RegisterComponent();
		StatComponent->SetData(StatDataTableRow);

		DefenceFloatingPawnMovement->MaxSpeed = StatComponent->GetSpeed();
	}

	for (int32 i = 0; i < SkeletalMeshComponent->GetNumMaterials(); ++i)
	{
		SkeletalMeshComponent->CreateDynamicMaterialInstance(i);
	}

	// 타임라인에 커브, 델리게이트 연결
	FOnTimelineFloat Delegate;
	Delegate.BindUFunction(this, TEXT("OnTimelineFloat"));
	TimelineComponent->AddInterpFloat(CurveFloat, Delegate);

	// 종료 델리게이트 연결
	FOnTimelineEvent TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("OnTimelineFinished"));
	TimelineComponent->SetTimelineFinishedFunc(TimelineFinishedCallback);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	TArray<AActor*> Array;
	GetAttachedActors(Array);
	for (AActor* Actor : Array)
	{
		if (Cast<AProjectile>(Actor))
		{
			Actor->Destroy();
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Damage = StatComponent->ProcessDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (StatComponent->GetHP() <= 0.0f)
	{
		// Stop movement
		GetController()->StopMovement();

		SetActorEnableCollision(false);
		TimelineComponent->PlayFromStart();
	}
	return Damage;
}

void AEnemy::OnTimelineFloat(float Value)
{
	for (auto Material : SkeletalMeshComponent->GetMaterials())
	{
		UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(Material);
		if (MID)
		{
			MID->SetScalarParameterValue(TEXT("PaperBurnOffset"), Value);
		}
	}

	// Projectile PaperBurn
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* Actor : AttachedActors)
	{
		AProjectile* Projectile = Cast<AProjectile>(Actor);
		if (Projectile)
		{
			TArray<UStaticMeshComponent*> Components;
			Projectile->GetComponents(UStaticMeshComponent::StaticClass(), Components);
			for (UStaticMeshComponent* StaticMeshComponent : Components)
			{
				for (int32 i = 0; i < StaticMeshComponent->GetNumMaterials(); ++i)
				{

					UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(StaticMeshComponent->GetMaterial(i));
					if (MID)
					{
						MID->SetScalarParameterValue(TEXT("PaperBurnOffset"), Value);
					}
				}
			}
		}
	}
}

void AEnemy::OnTimelineFinished()
{
	Destroy();
}

