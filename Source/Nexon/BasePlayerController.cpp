// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "BaseCharacter.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	ABaseCharacter * PlayerCharacter = Cast<ABaseCharacter>(GetCharacter());
	PlayerCharacter->InputComponent->BindAction("UseMouse", IE_Pressed, this, &ABasePlayerController::SetControllerAsMouse);
	PlayerCharacter->InputComponent->BindAction("UseGamepad", IE_Pressed, this, &ABasePlayerController::SetControllerAsGamepad);
}

void ABasePlayerController::SetControllerAsMouse()
{
	if (IsUsingGamepad) 
	{ 
		IsUsingGamepad = false; 
		bShowMouseCursor = true;
	}
}

void ABasePlayerController::SetControllerAsGamepad()
{
	if (!IsUsingGamepad) 
	{ 
		IsUsingGamepad = true; 
		bShowMouseCursor = false;
	}
}

bool ABasePlayerController::IsControllerAGamepad() const
{
	return IsUsingGamepad;
}
