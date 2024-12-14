// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class ALantern;
class ALanternHook;
class UInputAction;
UCLASS()
class LITTHEFIRE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	
	
	UPROPERTY(EditAnywhere, Category=Input)
	class UInputMappingContext*  InputMapping;
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, Category=Input)
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category=InteractParams)
	float InteractRange = 250.f;
	UPROPERTY(EditAnywhere, Category=InteractParams)
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Interact();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void GrabLantern(ALanternHook* Hook,FName SocketName);

	UPROPERTY()
	ALantern* LanternActor;


public:
	void SetLanternActor(ALantern* NewLanternActor)
	{
		LanternActor = NewLanternActor;
	}

	UFUNCTION(BlueprintCallable)
	bool HasGrabLantern() const
	{
		return LanternActor != nullptr;
	}

	UPROPERTY(editanywhere, BlueprintReadOnly)
	FName NextLevel = "Level1";
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};


