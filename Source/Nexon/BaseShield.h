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
	/*Radius of circle on which shield pieces will be spawned*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Radius;
	/*Indicates rotation speed of imagined circle with shield pieces*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float FloatingSpeed;
	/*Indicates how many shield pieces will be spawned on imagined circle*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		int32 NumberOfPieces;
	/*Class of shield pieces that will be spawned*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		TSubclassOf<ABaseShieldPiece> ShieldPieceClass;
private:
	/*Difference in rotation calculated based on parameters*/
	FRotator DeltaRotation;
	/*Totally meaningless Rules that just MUST be here*/
	const FActorSpawnParameters &SpawnParameters = FActorSpawnParameters();
	const FAttachmentTransformRules &AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	/*Array consisting of all spawned shield pieces of NumberOfPieces length*/
	TArray<ABaseShieldPiece*> ShieldPieces;

//Functions
public:
	/*Spawns shield pieces and place them on a circle*/
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
