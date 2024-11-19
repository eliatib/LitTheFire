// Fill out your copyright notice in the Description page of Project Settings.


#include "LitFire.h"

// Sets default values
ALitFire::ALitFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FireMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lantern Mesh"));
	FireMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALitFire::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALitFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ALitFire::GetLitId() const
{
	return LitId;
}

UMaterialInterface* ALitFire::GetMaterial() const
{
	return FireMesh->GetMaterial(0);
}

