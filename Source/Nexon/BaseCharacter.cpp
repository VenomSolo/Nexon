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

	objects.Add((UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic)));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ABasePlayerController>(GetController());
	bUsesGamepad = &(PlayerController->IsUsingGamepad);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (*bUsesGamepad)
	{
		Rotation = UKismetMathLibrary::FindLookAtRotation(this->GetTargetLocation(), this->GetTargetLocation() + FVector(RotationX, RotationY, 0));
		this->SetActorRotation(Rotation);
	}
	else {
		FHitResult hitResult;
		PlayerController->GetHitResultUnderCursorForObjects(objects, true, hitResult);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), hitResult.ImpactPoint).Yaw, 0.0f));
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Part for gamepad
	PlayerInputComponent->BindAxis("RotateRight", this, &ABaseCharacter::SetRotationY);
	PlayerInputComponent->BindAxis("RotateForward", this, &ABaseCharacter::SetRotationX);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABaseCharacter::StopFiring);
	PlayerInputComponent->BindAction("FireAlternative", IE_Pressed, this, &ABaseCharacter::FireAlternative);
	//Part for mouse
	PlayerInputComponent->BindAxis("MoveForwardMouse", this, &ABaseCharacter::MoveForwardMouse);
	PlayerInputComponent->BindAxis("MoveRightMouse", this, &ABaseCharacter::MoveRightMouse);
	PlayerInputComponent->BindAction("FireMouse", IE_Pressed, this, &ABaseCharacter::FireMouse);
	PlayerInputComponent->BindAction("FireMouse", IE_Released, this, &ABaseCharacter::StopFiringMouse);
	PlayerInputComponent->BindAction("FireAlternativeMouse", IE_Pressed, this, &ABaseCharacter::FireAlternativeMouse);
}

void ABaseCharacter::MoveForward(float Value)
{
	if (*bUsesGamepad == true)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			AddMovementInput(FORWARDVECTOR, Value);
		}
	}
}

void ABaseCharacter::MoveForwardMouse(float Value)
{
	if (*bUsesGamepad == false)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			AddMovementInput(FORWARDVECTOR, Value);
		}
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (*bUsesGamepad == true)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			AddMovementInput(RIGHTVECTOR, Value);
		}
	}
}

void ABaseCharacter::MoveRightMouse(float Value)
{
	if (*bUsesGamepad == false)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			AddMovementInput(RIGHTVECTOR, Value);
		}
	}
}

void ABaseCharacter::SetRotationX(float Value)
{
	if (*bUsesGamepad == true) {
		if ((Controller != NULL) && (Value != 0.0f))
		{
			RotationX = Value;
		}
	}
}

void ABaseCharacter::SetRotationY(float Value)
{
	if (*bUsesGamepad == true)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			RotationY = Value;
		}
	}
}

void ABaseCharacter::Fire()
{
}

void ABaseCharacter::FireMouse()
{
}

void ABaseCharacter::StopFiring()
{
}

void ABaseCharacter::StopFiringMouse()
{
}

void ABaseCharacter::FireAlternative()
{
}

void ABaseCharacter::FireAlternativeMouse()
{
}

void ABaseCharacter::AttachCorpse(UClass CorpseClass)
{
	if (GetCorpse() == nullptr) 
	{
		Corpse = GetWorld()->SpawnActor<ABaseCorpse>(&CorpseClass);
		Corpse->AttachToActor(this, AttachmentRules);
		Movement->MaxWalkSpeed = Corpse->Speed;
	}
}

void ABaseCharacter::DetachCorpse()
{
	if (Corpse != nullptr)
	{
		Corpse->Destroy();
		Corpse = nullptr;
	}
}

void ABaseCharacter::AttachShield(UClass ShieldClass)
{
	if (GetCorpse() != nullptr && GetShield() == nullptr) 
	{
		Shield = GetWorld()->SpawnActor<ABaseShield>(&ShieldClass);
		GetShield()->AttachToActor(Corpse, AttachmentRules);
	}
}

void ABaseCharacter::DetachShield()
{
	if (GetCorpse() != nullptr && GetShield() != nullptr)
	{
		GetShield()->Destroy();
		Shield = nullptr;
	}
}

void ABaseCharacter::AttachWeapon(int Index, UClass WeaponClass)
{
	if (GetCorpse() != nullptr && Weapons[Index] == nullptr && Index >= 0 && Index < GetCorpse()->SocketNames.Num())
	GetWeapons()[Index] = GetWorld()->SpawnActor<ABaseWeapon>(&WeaponClass);
	GetWeapons()[Index]->AttachToActor(Corpse, AttachmentRules, Corpse->SocketNames[Index]);
	GetWeapons()[Index]->SetActorRelativeLocation(FVector(0, 0, 0));
}

void ABaseCharacter::DetachWeapon(int Index)
{
	if (GetCorpse() != nullptr && Weapons[Index] != nullptr&& Index >= 0 && Index < GetCorpse()->SocketNames.Num())
	GetWeapons()[Index]->Destroy();
	GetWeapons()[Index] = nullptr;
}

void ABaseCharacter::InitializeProjectileSubPool()
{
	for (ABaseWeapon * Weapon : Weapons) 
	{
		AMainActorPool::InitializeSubPool(Weapon->Name);
	}
}
