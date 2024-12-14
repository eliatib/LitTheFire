// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LanternHook.generated.h"

class APointLight;
class ALantern;

UCLASS()
class LITTHEFIRE_API ALanternHook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALanternHook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ALantern* AttachedLantern;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetAttachLantern(ALantern* Lantern);

	UFUNCTION()
	ALantern* GetAttachLantern() const
	{
		return AttachedLantern;
	};
	
	UPROPERTY(EditAnywhere)
	bool bOnSide = false;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

};


