// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	// ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ReachLineStart = GetComponentLocation();
	FVector ReachLineEnd = ReachLineStart + (GetForwardVector() * MaxGrabDistance);

	DrawDebugLine(GetWorld(), ReachLineStart, ReachLineEnd, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		ReachLineStart,
		ReachLineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	if (!HasHit) return;
	UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *HitResult.GetActor()->GetActorNameOrLabel());
}

