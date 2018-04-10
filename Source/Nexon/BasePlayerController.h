// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"


class ABaseCharacter;
/**
 * 
 */
UCLASS()
class NEXON_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Defines current controller
	bool IsUsingGamepad;

private:
	virtual void BeginPlay() override;

	//Changes active controller
	void SetControllerAsMouse();
	void SetControllerAsGamepad();

public:
	//Cheks what is current controller
	bool IsControllerAGamepad() const;
	
};
