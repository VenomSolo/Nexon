// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class NEXON_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Particle component for projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles)
		class UParticleSystemComponent* Projectile;

	// Particle component played when projectile hits something
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles)
		class UParticleSystemComponent* OnProjectileHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
		class UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh;

	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Speed;	
	// Projectile hit power for enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Power;	
	// Projectile hit power for protection shields
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float ShieldPenetration;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void MoveProjectile();
	
};
