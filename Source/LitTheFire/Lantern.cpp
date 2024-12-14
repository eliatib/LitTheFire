// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"

#include "LitActor.h"
#include "MyCharacter.h"
#include "Components/PointLightComponent.h"
#include "Engine/PointLight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALantern::ALantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LanternMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lantern Mesh"));
	LanternMesh->SetupAttachment(RootComponent);
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PLight"));
	Light->SetupAttachment(LanternMesh);

}

void ALantern::RefreshLitActorList()
{
	LitActors.Empty();
	if (!LitActorClass) return;
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), LitActorClass.Get(),Actors);
	for (AActor* Actor : Actors)
	{
		if (ALitActor* Lit = Cast<ALitActor>(Actor))
		{
			if (Lit->GetLitGroup() == LitId)
			{
				LitActors.Add(Lit);
				VerifyPositionToLitActors();
			}
		}
	}
}

// Called when the game starts or when spawned
void ALantern::BeginPlay()
{
	Super::BeginPlay();
	RefreshLitActorList();
	if (!MaterialLight) return;
	MID = LanternMesh->CreateDynamicMaterialInstance(1,MaterialLight);
	if (!MID || !Light) return;
	MID->SetVectorParameterValue(TEXT("Light Color"),Light->GetLightColor());
	RefreshLitActorList();
	if (StartLantern)
	{
		AActor* Player =  UGameplayStatics::GetPlayerPawn(GetWorld(),0);
		if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(Player))
		{
			LanternMesh->SetSimulatePhysics(false);
			LanternMesh->SetEnableGravity(false);
			AttachToComponent(MyCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "LanternSocket");
			SetOwner(MyCharacter);
			MyCharacter->SetLanternActor(this);
		}
	}
}

// Called every frame
void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VerifyPositionToLitActors();

}

void ALantern::VerifyPositionToLitActors()
{
	for (ALitActor* LitActor : LitActors)
	{
		if (LitActor != nullptr )
		{
			FVector LanternLocation = GetActorLocation();
			FLinearColor LanternColor = FLinearColor(LanternLocation.X, LanternLocation.Y, LanternLocation.Z, 1.f);
			LitActor->SetPos(LanternColor);
		}
	}
}
