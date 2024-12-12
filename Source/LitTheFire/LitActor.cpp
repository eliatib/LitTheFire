// Fill out your copyright notice in the Description page of Project Settings.


#include "LitActor.h"

#include "Lantern.h"
#include "VIBaseTransformGizmo.h"
#include "Components/BoxComponent.h"
#include "DSP/MidiNoteQuantizer.h"
#include "DynamicMesh/MeshTransforms.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALitActor::ALitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ALitActor::OnConstruction(const FTransform& Transform)
{
	SetActorEnableCollision(!bInverseTransparency);
	if (!Material) return;
	MID = Mesh->CreateDynamicMaterialInstance(0,Material);
	if (!MID) return;
	MID->SetVectorParameterValue(TEXT("pos"),Pos);
	MID->SetVectorParameterValue(TEXT("Transparency"),bInverseTransparency? FColor::Green : FColor::Red );
	SetCollision(true);
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALantern::StaticClass(),Actors);
	for (AActor* Actor : Actors)
	{
		if (ALantern* Lantern = Cast<ALantern>(Actor))
		{
			Lantern->RefreshLitActorList();
		}
	}
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void ALitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FLinearColor ALitActor::GetPos() const
{
	return Pos;
}

void ALitActor::SetPos(const FLinearColor NewPos)
{
	Pos = NewPos;
	MID->SetVectorParameterValue(TEXT("pos"),Pos);
	auto Distance = (GetActorLocation() - FVector(Pos.R,Pos.G,Pos.B)).Size();
	SetCollision(Distance < 300.f);
}

int32 ALitActor::GetLitGroup() const
{
	return LitGroup;
}

void ALitActor::SetCollision(bool IsEnabled)
{
	SetActorEnableCollision( IsEnabled ? bInverseTransparency : !bInverseTransparency);
}
