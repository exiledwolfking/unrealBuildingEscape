// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "GameFramework/Actor.h"
#include <string>

using namespace std;
// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	AActor* actor = GetOwner();
	FString name = actor->GetName();
	FVector positionVector = actor->GetActorLocation();
	// FString x = FString::SanitizeFloat(positionVector.X);
	// FString y = FString::SanitizeFloat(positionVector.Y);
	// FString z = FString::SanitizeFloat(positionVector.Z);
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *name, *(positionVector.ToString()));

}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

