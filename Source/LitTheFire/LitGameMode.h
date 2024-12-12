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
	public:
	virtual void BeginPlay() override;
};
