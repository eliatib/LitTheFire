// Fill out your copyright notice in the Description page of Project Settings.


#include "LanternHook.h"

#include "Lantern.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
ALanternHook::ALanternHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ALanternHook::BeginPlay()
{
	Super::BeginPlay();
	if (AttachedLantern != nullptr)
	{
		SetAttachLantern(AttachedLantern);
	}
}

// Called every frame
void ALanternHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALanternHook::SetAttachLantern(ALantern* Lantern)
{
	if (AttachedLantern != nullptr)
	{
		AttachedLantern->SetActorEnableCollision(true);
	}
	AttachedLantern = Lantern;
	if (Lantern != nullptr)
	{ 
		FName LanternSocket = bOnSide ? FName("SocketLanternSide") : FName("SocketLanternDown");
		Lantern->AttachToActor(this,FAttachmentTransformRules::SnapToTargetNotIncludingScale, LanternSocket);
		Lantern->SetOwner(this);
		Lantern->SetActorEnableCollision(false);
	}
}
