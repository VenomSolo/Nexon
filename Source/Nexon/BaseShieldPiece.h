// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "BaseShieldPiece.generated.h"

UCLASS()
class NEXON_API ABaseShieldPiece : public AActor
{
	GENERATED_BODY()

public:
	/*It defines, how durable is shield.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float ShieldDurability;
	/*Defines how long takes to respawn a shield after destroing it.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float RespawnTime;
	/*Sets how fast shield is regenerating.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float RegenerationRate;

private:
		float CurrentDurability;	// Initialised in Begin Play

public:
	void RegenerateDurability();
	void StartRegenerate();
	void DecreaseCurrentDurabilityOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	ABaseShieldPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
