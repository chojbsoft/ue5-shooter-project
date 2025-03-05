// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineEnemySpawner.h"
#include "Enemy.h"

// Sets default values
ASplineEnemySpawner::ASplineEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(SplineComponent);
	StaticMeshComponent->SetupAttachment(SplineComponent);
}

// Called when the game starts or when spawned
void ASplineEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASplineEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASplineEnemySpawner::StartWave(UEnemySpawnDataAsset* InEnemySpawnDataAsset)
{
	if (InEnemySpawnDataAsset)
	{
		EnemySpawnDataAsset = InEnemySpawnDataAsset;
	}

	if (!EnemySpawnDataAsset)
	{
		return;
	}

	if (CurrentSpawnIndex >= EnemySpawnDataAsset->EnemySpawnInfoArray.Num())
	{
		return;
	}

	FEnemySpawnInfo& EnemySpawnInfo = EnemySpawnDataAsset->EnemySpawnInfoArray[CurrentSpawnIndex++];
	Spawn(EnemySpawnInfo, EnemySpawnInfo.SpawnCount);
}

void ASplineEnemySpawner::Spawn(FEnemySpawnInfo& InEnemySpawnInfo, const uint32 InRemainCount)
{
	GetWorldTimerManager().SetTimer(TimerHandle, [this, &InEnemySpawnInfo, InRemainCount]()
		{
			FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(InEnemySpawnInfo.EnemyClass, SpawnTransform, Param);

			// SplineComponent가 가진 포인트의 개수를 얻습니다.
			TArray<FVector> Points;
			int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
			for (int32 i = 0; i < NumPoints; i++)
			{
				FVector PointLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
				Points.Add(PointLocation);
			}
			Cast<AFollowPointsAIController>(Enemy->GetController())->SetPointsAndMove(Points);


			// 다 소환했으면 다음 웨이브, 남아있다면 다음 스폰
			if (InRemainCount == 1)
			{
				StartWave(nullptr);
			}
			else
			{
				Spawn(InEnemySpawnInfo, InRemainCount - 1);
			}

		}, InEnemySpawnInfo.SpawnDelay, false);
}


