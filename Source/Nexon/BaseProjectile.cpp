// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"




// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	Collision->SetCapsuleHalfHeight(60.f);
	Collision->SetCapsuleRadius(26.f);
	Collision->bGenerateOverlapEvents = true;
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapBegin);

	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision); 
	
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(Collision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInitialVelocityInLocalSpace = false;
	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = Speed;
	
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
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());	// Play HitParticle 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Projectile hit something");
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseProjectile::OnTimerExpire, DestroyDelay, false);
	}
}

void ABaseProjectile::OnTimerExpire()
{
	Destroy();
}











