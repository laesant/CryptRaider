// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released grabber"));
}

void UGrabber::Grab()
{
	if (UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle())
	{
		FVector Start = GetComponentLocation();
		FVector End = Start + GetForwardVector() * MaxGrabDistance;
		DrawDebugLine(GetWorld(), Start, End, FColor::Red);
		// DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5.f);

		FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
		FHitResult HitResult;
		bool HasHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			Start,
			End,
			FQuat::Identity,
			ECC_GameTraceChannel2,
			Sphere);
		if (HasHit)
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				HitResult.GetComponent(),
				NAME_None,
				HitResult.ImpactPoint,
				GetComponentRotation());
		}
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	if (UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>())
	{
		return PhysicsHandle;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Don't Have a UPhysicsHandleComponent"));
		return nullptr;
	}
}



