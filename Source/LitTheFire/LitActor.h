// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Util/ColorConstants.h"
#include "LitActor.generated.h"

class ALantern;

UCLASS()
class LITTHEFIRE_API ALitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	int32 LitGroup = 0;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* Material;
	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* MID;
	UPROPERTY(VisibleAnywhere)
	FLinearColor Pos;

public:
	FLinearColor GetPos() const;
	void SetPos(const FLinearColor& NewPos);
	void SetCollision(bool IsEnabled);

private:
	UPROPERTY(EditAnywhere)
	bool bInverseTransparency = false;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetLitGroup() const;
};

