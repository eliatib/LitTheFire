// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Lantern.h"
#include "LanternHook.h"
#include "LitFire.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (InputMapping != nullptr)
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		Input->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyCharacter::Interact);
		// Looking
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
	}
}

void AMyCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
	if (AController* OC = GetController())
	{
		FHitResult Hit;
		FVector CamLoc;
		FRotator CamRot;
		OC->GetPlayerViewPoint(CamLoc,CamRot);
		FVector End = CamLoc + CamRot.Vector() * InteractRange;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		GetWorld()->LineTraceSingleByChannel(Hit,CamLoc,End,ECollisionChannel::ECC_WorldDynamic, Params);
		DrawDebugLine(GetWorld(),CamLoc,End,FColor::Red,true);
		if (Hit.GetActor() != nullptr)
		{
			if (Hit.GetActor()->GetClass()->IsChildOf(ALanternHook::StaticClass()))
			{
				ALanternHook* Hook = Cast<ALanternHook>(Hit.GetActor());
				if (Hook != nullptr)
				{
					GrabLantern(Hook,TEXT("LanternSocket"));
				}
			}
		}
	}
}

void AMyCharacter::GrabLantern(ALanternHook* Hook,FName SocketName)
{
	ALantern* HookLantern = Hook->GetAttachLantern();
	if (HookLantern != nullptr)
	{
		HookLantern->LanternMesh->SetSimulatePhysics(false);
		HookLantern->LanternMesh->SetEnableGravity(false);
		HookLantern->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
		HookLantern->SetOwner(this);
	}
	Hook->SetAttachLantern(LanternActor);
	LanternActor = HookLantern;
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

