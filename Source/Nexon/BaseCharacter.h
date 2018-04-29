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
	/*Pointers to aircraft components*/
	ABaseCorpse* Corpse;
	ABaseShield* Shield;
	TArray<ABaseWeapon*> Weapons;
	TArray<ABaseWeapon*> NormalWeapons;
	TArray<ABaseWeapon*> AlternativeWeapons;
	/*Constant vectors used for movement*/
	const FVector FORWARDVECTOR = FVector(1.0, 0.0, 0.0);
	const FVector RIGHTVECTOR = FVector(0.0, 1.0, 0.0);
	/*Mouse pointer current coordinates used to determine rotation*/
	float RotationX;
	float RotationY;
	/*Current aircraft rotation*/
	FRotator Rotation;
	/*Indicates what the current controller is*/
	bool * bUsesGamepad;
	/*Types of objects that mouse raycasts collide with*/
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	/*Totally meaningless Rules that just MUST be here*/
	const FActorSpawnParameters &SpawnParameters = FActorSpawnParameters();
	const FAttachmentTransformRules &AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	/*Pointer to PlayerController*/
	ABasePlayerController * PlayerController;

//Functions
public:
	//Getters for aircraft components
	FORCEINLINE ABaseCorpse* GetCorpse() {
		return Corpse;
	}
	FORCEINLINE ABaseShield* GetShield() {
		return Shield;
	}
	FORCEINLINE TArray<ABaseWeapon*> GetWeapons() {
		return Weapons;
	}
	FORCEINLINE TArray<ABaseWeapon*> GetNormalWeapons() {
		return NormalWeapons;
	}
	FORCEINLINE TArray<ABaseWeapon*> GetAlternativeWeapons() {
		return AlternativeWeapons;
	}
protected:
	UFUNCTION(BlueprintCallable)
	void AttachCorpse(UClass * Corpse);
	UFUNCTION(BlueprintCallable)
	void DetachCorpse();
	UFUNCTION(BlueprintCallable)
	void AttachShield(UClass * Shield);
	void DetachShield();
	UFUNCTION(BlueprintCallable)
	void AttachWeapon(int Index, UClass * WeaponClass);
	UFUNCTION(BlueprintCallable)
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
	void DeepFire();
	void StopFiring();
	void StopFiringMouse();
	void DeepStopFiring();
	void FireAlternative();
	void FireAlternativeMouse();
	void DeepFireAlternative();










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

