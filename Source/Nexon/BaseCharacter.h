// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class NEXON_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	const FVector FORWARDVECTOR = FVector(1.0, 0.0, 0.0);
	const FVector RIGHTVECTOR = FVector(0.0, 1.0, 0.0);
	float RotationX;
	float RotationY;
	FRotator Rotation;
	bool * bUsesGamepad;
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;

	ABasePlayerController * PlayerController;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	/*Side movement speed of our aircraft.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float SpeedHorizontal;
	/*Set the forward speed of our aircraft.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float SpeedForward;
	/*Set the backward speed of our aircraft.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float SpeedBackward;
	/*Side tilting.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Tilt;
	/*Weight of aircraft that influence on its speed.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float Weight;
	/*Number of tries. If our aircraft is destroyed, decreases by 1.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		int Lives;
	/*This is a radius that can reach opponents.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float ShootRange;
	/*This is how far our projectile hits.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float ShootDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
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
	
};

