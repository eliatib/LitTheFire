// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

UCLASS()
class LITTHEFIRE_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALantern();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	UPROPERTY(EditAnywhere,Category=component)
	USkeletalMeshComponent* LanternMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Lantern")
	void AttachLantern(AMyCharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable, Category = "Lantern")
	void SetMaterial(UMaterialInterface* Material);
};
