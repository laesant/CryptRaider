// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	/*int32 index = 0;
	while (index < Actors.Num())
	{
		++index;
	}*/

	for (int32 i = 0; i < Actors.Num(); i++)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *Actors[i]->GetActorNameOrLabel());
	}
}
