// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"
#include "MainActorPool.h"
#include "BaseWeapon.generated.h"

UCLASS()
class NEXON_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

//Components
private:
	//StaticMesh of this weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;


//Variables
public:
	//Class of the projectile to be spawned when fired
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		TSubclassOf<ABaseProjectile> Projectile;
	//Name of this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		FName Name;

private:
	//Index of SubPool with stored projectiles of class Projectile
	int32 AmmoPoolIndex;
	//List of sockets' names in which projectiles will be spawned
	TArray<FName> SocketNames;

//Functions
public:
	//Spawns projectiles in all sockets
	void Fire();










//Engine stuff
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
