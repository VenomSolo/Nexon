// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "BaseWeapon.h"
#include "BaseShield.h"
#include "BaseCorpse.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class NEXON_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

//Components
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCharacterMovementComponent* Movement;
//Variables
private:
	ABaseCorpse* Corpse;
	ABaseShield* Shield;
	TArray<ABaseWeapon*> Weapons;
	const FVector FORWARDVECTOR = FVector(1.0, 0.0, 0.0);
	const FVector RIGHTVECTOR = FVector(0.0, 1.0, 0.0);
	float RotationX;
	float RotationY;
	FRotator Rotation;
	bool * bUsesGamepad;
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	const FActorSpawnParameters &SpawnParameters = FActorSpawnParameters();
	const FAttachmentTransformRules &AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	ABasePlayerController * PlayerController;

//Functions
public:
	FORCEINLINE ABaseCorpse* GetCorpse() {
		return Corpse;
	}
	FORCEINLINE ABaseShield* GetShield() {
		return Shield;
	}
	FORCEINLINE TArray<ABaseWeapon*> GetWeapons() {
		return Weapons;
	}
protected:
	void AttachCorpse(UClass Corpse);
	void DetachCorpse();
	void AttachShield(UClass Shield);
	void DetachShield();
	void AttachWeapon(int Index, UClass WeaponClass);
	void DetachWeapon(int Index);
	void InitializeProjectileSubPool();
	void SetRotationX(float Value);
	void SetRotationY(float Value);
	void MoveForward(float Value);
	void MoveForwardMouse(float Value);
	void MoveRight(float Value);
	void MoveRightMouse(float Value);
	void Fire();
	void FireMouse();
	void StopFiring();
	void StopFiringMouse();
	void FireAlternative();
	void FireAlternativeMouse();










//Engine Stuff
public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};

