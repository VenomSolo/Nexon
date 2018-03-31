// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"
#include "BaseShieldPiece.h"
#include "BaseShield.generated.h"

UCLASS()
class NEXON_API ABaseShield : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float FloatingSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		int32 NumberOfPieces;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		TSubclassOf<ABaseShieldPiece> ShieldPieceClass;
private:
	FRotator DeltaRotation;
	const FActorSpawnParameters &SpawnParameters = FActorSpawnParameters();
	const FAttachmentTransformRules &AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	TArray<ABaseShieldPiece*> ShieldPieces;

//Functions
public:
	void InitializeShield();









//Engine stuff
public:	
	// Sets default values for this actor's properties
	ABaseShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
