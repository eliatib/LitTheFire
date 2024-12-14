// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class LITTHEFIRE_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
public:

	ACharacterController();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY()
	UUserWidget* LanternWidget;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowWidget();

	// Hide the widget
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideWidget();

	//Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundCue* AmbientSound;

	// Composant audio
	UPROPERTY()
	UAudioComponent* AudioComponent;

	// Fonction pour jouer l'ambiance sonore
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayAmbientSound();

	// Fonction pour arrêter l'ambiance sonore
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopAmbientSound();
};
