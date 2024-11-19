// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LitFire.generated.h"

UCLASS()
class LITTHEFIRE_API ALitFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALitFire();
	UPROPERTY(EditAnywhere,Category=component)
	USkeletalMeshComponent* FireMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category=Component)
	int LitId = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int GetLitId() const;
	UMaterialInterface* GetMaterial() const;
};

