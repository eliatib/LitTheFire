// Fill out your copyright notice in the Description page of Project Settings.


#include "UHandGrabber.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values for this component's properties
UHandGrabber::UHandGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHandGrabber::Grab(AActor* Actor,USkeletalMeshComponent* Mesh, const FName SocketName)
{
	if (Mesh->DoesSocketExist(SocketName))
	{
		Actor->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform, SocketName);
		Actor->SetOwner(Mesh->GetOwner());
		bIsGrabbed = true;
	}
}

// Called when the game starts
void UHandGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHandGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

