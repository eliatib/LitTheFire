// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ACharacterController::ACharacterController()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	// Jouer le son d'ambiance quand le jeu commence
	PlayAmbientSound();
}


void ACharacterController::ShowWidget()
{
	if (WidgetClass && !LanternWidget)
	{
		// Create the widget and add it to the viewport
		LanternWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (LanternWidget)
		{
			LanternWidget->AddToViewport();
			LanternWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ACharacterController::HideWidget()
{
	if (LanternWidget)
	{
		// Remove the widget from the viewport and nullify the pointer
		LanternWidget->SetVisibility(ESlateVisibility::Hidden);
		LanternWidget = nullptr;
	}
}


void ACharacterController::PlayAmbientSound()
{
	if (AmbientSound && AudioComponent)
	{
		// Jouer le son en boucle
		AudioComponent->SetSound(AmbientSound);
		AudioComponent->Play();
	}
}

void ACharacterController::StopAmbientSound()
{
	if (AudioComponent && AudioComponent->IsPlaying())
	{
		// Arrêter le son
		AudioComponent->Stop();
	}
}