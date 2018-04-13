// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseShieldPiece.h"


// Sets default values
ABaseShieldPiece::ABaseShieldPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseShieldPiece::DecreaseCurrentDurabilityOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// If something hits Shield, then decrease current durability
	ABaseProjectile Object;
	CurrentDurability -= Object.ShieldPenetration;
	if (CurrentDurability <= 0) 
	{
		SetActorEnableCollision(false);		// Turn off collision
		SetActorHiddenInGame(true);		// Hide Actor
	}
}

void ABaseShieldPiece::StartRegenerate()
{
	if (CurrentDurability <= 0)
	{
		// Call RegenerateDurability function after RespawnTime expire
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseShieldPiece::RegenerateDurability, RespawnTime, false);
	}
}

void ABaseShieldPiece::RegenerateDurability()
{
	if (CurrentDurability <= ShieldDurability)
	{
		CurrentDurability += RegenerationRate * GetWorld()->TimeSeconds;
	}
	else	// Durability Regeneration off...
	{		
		SetActorEnableCollision(true);
		SetActorHiddenInGame(false);
	}
}

// Called when the game starts or when spawned
void ABaseShieldPiece::BeginPlay()
{
	Super::BeginPlay();
	CurrentDurability = ShieldDurability;
}

// Called every frame
void ABaseShieldPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RegenerateDurability();
	StartRegenerate();
}



