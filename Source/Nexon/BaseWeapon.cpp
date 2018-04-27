// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"



void ABaseWeapon::Fire()
{
	if (IsFiring == true)
	{
		int8 index = 0;
		for (FName Socket : SocketNames) {
			ABaseProjectile * NewProjectile = Cast<ABaseProjectile>(AMainActorPool::GetUnusedFromSubPool(SocketsLocations[index], AmmoPoolIndex));
		}
	}
	GetWorldTimerManager().SetTimer(DelayTimer, &Fire, FireInterval, false);
}

void ABaseWeapon::StartFire()
{
	IsFiring = true;
	Fire();
}

void ABaseWeapon::StopFire()
{
	IsFiring = false;
}

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SocketNames = Mesh->GetAllSocketNames();
	for (FName &SocketName : SocketNames) 
	{
		SocketsLocations.Add(Mesh->GetSocketTransform(SocketName));
	}
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

