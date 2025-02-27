// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

USTRUCT()
struct FProjectileDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
	FTransform StaticMeshTransform;

	UPROPERTY(EditAnywhere)
	float ColliderRadius = 32.f;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 2000.f;

	UPROPERTY(EditAnywhere)
	float FireDelay = 0.2f;

	UPROPERTY(EditAnywhere)
	float InitialLifeSpan = 5.f;

	UPROPERTY(EditAnywhere)
	TArray<UMaterial*> Materials;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle FireEffect;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle HitEffect;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float DamageRadius;
};



UCLASS()
class SHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	void SetData(FProjectileDataTableRow* Row);

protected:
	UFUNCTION()
	void OnActorHitFunction(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;

	FProjectileDataTableRow* ProjectileDataTableRow;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle EffectDataTableRowHandle;

};
