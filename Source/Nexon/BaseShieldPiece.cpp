// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseShieldPiece.h"


// Sets default values
ABaseShieldPiece::ABaseShieldPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseShieldPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseShieldPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

