// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"

#include "MyCharacter.h"

// Sets default values
ALantern::ALantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LanternMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lantern Mesh"));
	LanternMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALantern::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALantern::AttachLantern(AMyCharacter* PlayerCharacter)
{
	// Check that the character is valid, and has no rifle yet
	if (PlayerCharacter == nullptr || PlayerCharacter->AsGrabLantern())
	{
		return;
	}
	LanternMesh->SetSimulatePhysics(false);
	LanternMesh->SetEnableGravity(false);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(PlayerCharacter->GetMesh(), AttachmentRules, FName(TEXT("LanternSocket")));
}

void ALantern::SetMaterial(UMaterialInterface* Material)
{
	LanternMesh->SetMaterial(1, Material);
}

// Called every frame
void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

