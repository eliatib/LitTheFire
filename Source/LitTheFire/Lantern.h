// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

class UPointLightComponent;
class APointLight;
class ALitActor;

UCLASS()
class LITTHEFIRE_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALantern();
	void RefreshLitActorList();
	virtual void OnConstruction(const FTransform& Transform) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=ID)
	int LitId = 0;

	


	UPROPERTY(EditAnywhere)
	UMaterialInterface* MaterialLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* MID;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Lantern")
	void VerifyPositionToLitActors();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool StartLantern = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool LanternClin = false;
	
	int GetLitId() const
	{
		return LitId;
	}

	void SetLitId(int NewLitId)
	{
		LitId = NewLitId;
		RefreshLitActorList();
	}

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> LitActorClass;
	UPROPERTY(visibleAnywhere)
	TArray<ALitActor*> LitActors;
	UPROPERTY(EditAnywhere,Category=component)
	USkeletalMeshComponent* LanternMesh;
	
	UPROPERTY(EditAnywhere,blueprintReadWrite,Category=Light)
	UPointLightComponent* Light;
};

inline void ALantern::OnConstruction(const FTransform& Transform)
{
	RefreshLitActorList();
	Super::OnConstruction(Transform);
}

