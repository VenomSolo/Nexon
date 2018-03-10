// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	Camera->SetIsReplicated(false);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotation = UKismetMathLibrary::FindLookAtRotation(this->GetTargetLocation(), this->GetTargetLocation() + FVector(RotationX, RotationY, 0));
	this->SetActorRotation(Rotation);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("RotateRight", this, &ABaseCharacter::SetRotationY);
	PlayerInputComponent->BindAxis("RotateForward", this, &ABaseCharacter::SetRotationX);
	PlayerInputComponent->BindAction("Fire", this, &ABaseCharacter::Fire);
	PlayerInputComponent->BindAction("FireAlternative", this, &ABaseCharacter::FireAlternative);

}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{ 
		AddMovementInput(FORWARDVECTOR, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddMovementInput(RIGHTVECTOR, Value);
	}
}

void ABaseCharacter::SetRotationX(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		RotationX = Value;
	}
}

void ABaseCharacter::SetRotationY(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		RotationY = Value;
	}
}

void ABaseCharacter::Fire()
{
}

void ABaseCharacter::FireAlternative()
{
}

