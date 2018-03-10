// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called for forwards/backward input 
	void MoveForward(float Value);

	// Called for side to side input 
	void MoveRight(float Value);

	void SetRotationX(float Value);

	void SetRotationY(float Value);

	void Fire();

	void FireAlternative();
	
};

/*"Plugins": [
{
"Name": "ActorPool",
"Enabled": true,
"MarketplaceURL": "com.epicgames.launcher://ue/marketplace/content/66efc9b030dc4fbe9523d72b06f43a79"
}
]*/