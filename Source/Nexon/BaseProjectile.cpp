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
	DestroyDelay = 0.15f;

	/*ProjectileHitLocation = (0.f, 0.f, 0.f);
	ProjectileHitRotation = (0.f, 0.f, 0.f);
	ProjectileHitScale = (1.f, 1.f, 1.f);*/
		
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	Collision->SetCapsuleHalfHeight(60.f);
	Collision->SetCapsuleRadius(26.f);
	Collision->bGenerateOverlapEvents = true;
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapBegin);

	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepWorldTransform, "Mesh");
	
		
	Projectile = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile"));
	Projectile->AttachToComponent(Collision, FAttachmentTransformRules::KeepWorldTransform, "Projectile");

	OnProjectileHit = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OnProjectileHit"));
	OnProjectileHit->AttachToComponent(Collision, FAttachmentTransformRules::KeepWorldTransform, "OnProjectileHit");
	OnProjectileHit->bGenerateOverlapEvents = true;
	OnProjectileHit->bAutoActivate = false;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInitialVelocityInLocalSpace = false;
	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = 300.f * Speed;
	Movement->Velocity = FVector(-1.f, 0.f, 0.f);
	
	SetActorRotation(GetActorRotation() + FRotator(90.f, 0.f, 0.f));
	
	
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


void ABaseProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// Set ProjectileHit particle visible
		
		OnProjectileHit->Activate();

		/*UParticleSystemComponent * SpawnEmitterAtLocation
		(
			const UObject * GetWorld(),
			UParticleSystem * OnProjectileHit,
			FVector ProjectileHitLocation,
			FRotator ProjectileHitRotation,
			FVector ProjectileHitScale,
			bool bAutoDestroy = true
		);*/

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Projectile hitted something");

		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseProjectile::OnTimerExpire, DestroyDelay, false);
	}
}

void ABaseProjectile::OnTimerExpire()
{
	Destroy();
}











