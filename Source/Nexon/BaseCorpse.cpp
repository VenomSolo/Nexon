// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCorpse.h"


// Sets default values
ABaseCorpse::ABaseCorpse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ABaseCorpse::BeginPlay()
{
	Super::BeginPlay();
	SocketNames = Mesh->GetAllSocketNames();
}

// Called every frame
void ABaseCorpse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

