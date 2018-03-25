// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"
#include "BaseWeapon.generated.h"

UCLASS()
class NEXON_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	//Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		TSubclassOf<ABaseProjectile> Projectile;


public:
	void Fire();



public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
