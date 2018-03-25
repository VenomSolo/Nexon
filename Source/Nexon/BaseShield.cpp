// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseShield.h"


void ABaseShield::InitializeShield()
{
	FVector Forward = GetActorForwardVector();
	FRotator Rot = Forward.Rotation();
	DeltaRotation = FRotator(0, FloatingSpeed, 0);
	FVector Location;
	for (int i = 0; i < NumberOfPieces; i++)
	{
		Rot.Yaw += (360.0f/NumberOfPieces);
		Location = Rot.Vector() * Radius;
		AActor * NewShieldPieceActor = GetWorld()->SpawnActor(Cast<UClass>(ShieldPieceClass), new FVector(0,0,0), new FRotator(0,0,0), SpawnParameters);
		NewShieldPieceActor->AttachToActor(this, AttachmentRules);
		NewShieldPieceActor->AddActorLocalTransform(FTransform(Location));
		ABaseShieldPiece * NewShieldPiece = Cast<ABaseShieldPiece>(NewShieldPieceActor);
		ShieldPieces.Add(NewShieldPiece);	
	}
}

// Sets default values
ABaseShield::ABaseShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseShield::BeginPlay()
{
	Super::BeginPlay();
	InitializeShield();
}

// Called every frame
void ABaseShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->AddActorLocalRotation(DeltaRotation*DeltaTime);
}

