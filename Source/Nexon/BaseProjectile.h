// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseProjectile.generated.h"

UCLASS()
class NEXON_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Particle component for projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* Particle;

	/*Collision component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* Collision;

	/*StaticMesh component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	/*ProjectileMovement component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* Movement;

	// Particle played when projectile hits something
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		UParticleSystem* HitParticle;
	// Projectile movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Speed;
	// Projectile hit power for enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Power;
	// Projectile hit power for protection shields
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
	    float ShieldPenetration;
	// Delay for projectile destroying
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameters)
		float DestroyDelay;

	
public:

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnTimerExpire();
	

public:	
	// Sets default values for this actor's properties
	ABaseProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
