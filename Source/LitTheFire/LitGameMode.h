// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LitGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LITTHEFIRE_API ALitGameMode : public AGameModeBase
{
	GENERATED_BODY()

	protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TArray<AActor*> LitActors;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	int LitID = 0;
	
	public:
	virtual void BeginPlay() override;
	void ChangeLitId(int NewID);
};
