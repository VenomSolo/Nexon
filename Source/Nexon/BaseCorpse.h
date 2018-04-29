// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCorpse.generated.h"

UCLASS()
class NEXON_API ABaseCorpse : public AActor
{
	GENERATED_BODY()

//Components
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

//Variables
public:
	/*Speed of our aircraft.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Speed;
	/*Number of tries. If our aircraft is destroyed, decreases by 1.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Durability;

	TArray<FName> SocketNames;

//Functions













//Engine stuff
public:	
	// Sets default values for this actor's properties
	ABaseCorpse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
