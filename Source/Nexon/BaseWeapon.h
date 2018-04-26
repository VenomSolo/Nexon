// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"
#include "MainActorPool.h"
#include "BaseWeapon.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EWeaponTypeEnum : uint8
{
	VT_Normal 	UMETA(DisplayName = "Normal"),
	VT_Alternative 	UMETA(DisplayName = "Alternative"),
};

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
	//Indicates time of delay after firing once
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float FireInterval;
	//Index of SubPool with stored projectiles of class Projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		int32 AmmoPoolIndex;
	//Normal or altrnative?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		EWeaponTypeEnum WeaponType;

private:
	//Describes current state
	bool IsFiring;
	//List of sockets' names in which projectiles will be spawned
	TArray<FName> SocketNames;
	//List of sockets' locations in which projectiles will be spawned
	TArray<FTransform> SocketsLocations;
	//Handles fire delay
	FTimerHandle DelayTimer;

//Functions
public:
	//Spawns projectiles in all sockets
	void Fire();
	//Starts firing loop
	void StartFire();
	//Stops firing loop
	void StopFire();









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
