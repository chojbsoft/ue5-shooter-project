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

	SetRootComponent(BoxComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionProfileName(TEXT("Enemy"));

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

	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), DamageAmount);
	--HP;
	if (HP == 0)
	{
		Destroy();
	}

	return Damage;
}

