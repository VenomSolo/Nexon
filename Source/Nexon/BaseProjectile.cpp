// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 1.f;
	Power = 1000.f;
	ShieldPenetration = 100.f;
		
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->SetCapsuleHalfHeight(60.f);
	Collision->SetCapsuleRadius(26.f);
		
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepWorldTransform, "Mesh");
	//Mesh->SetWorldScale3D(GetActorScale() * 0.8);
	//Mesh->SetRelativeLocation(GetActorLocation() - FVector(0.f, 0.f, 40.f));
		
	Projectile = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile"));
	Projectile->AttachToComponent(Collision, FAttachmentTransformRules::KeepWorldTransform, "Projectile");

	OnProjectileHit = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OnProjectileHit"));
	OnProjectileHit->AttachToComponent(Collision, FAttachmentTransformRules::KeepWorldTransform, "OnProjectileHit");

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInitialVelocityInLocalSpace = false;
	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = 300.f * Speed;
	Movement->Velocity = FVector(-1.f, 0.f, 0.f);
	
	SetActorRotation(GetActorRotation() + FRotator(90.f, 0.f, 0.f));
	//SetActorScale3D(GetActorScale() * 0.5);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}








