// Fill out your copyright notice in the Description page of Project Settings.


#include "LitGameMode.h"

#include "LitActorComponent.h"
#include "Kismet/GameplayStatics.h"

void ALitGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (Actor->FindComponentByClass<ULitActorComponent>())
		{
			LitActors.Add(Actor);
		}
	}
}

void ALitGameMode::ChangeLitId(int NewID)
{
	
	for (AActor* Actor : LitActors)
	{
		if (ULitActorComponent* LitComponent = Actor->FindComponentByClass<ULitActorComponent>())
		{
			if (LitComponent->LitGroup == LitID)
			{
				Actor->SetActorHiddenInGame(true);
				Actor->SetActorEnableCollision(false);
				continue;
			}
			if (LitComponent->LitGroup == NewID)
			{
				UE_LOG(LogTemp, Display, TEXT("Change Id Lit to: %i"),NewID);
				Actor->SetActorHiddenInGame(false);
				Actor->SetActorEnableCollision(true);
			}
		}
	}
	LitID = NewID;
}
