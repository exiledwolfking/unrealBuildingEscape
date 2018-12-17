// Copyright Kyle Wahl 2018

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Owner = GetOwner();

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
}

void UOpenDoor::OpenDoor()
{
	FRotator newRotation = FRotator(0.0f, OpenAngle, 0.0f);
	Owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	FRotator newRotation = FRotator(0.0f, 0.0f, 0.0f);
	Owner->SetActorRotation(newRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the triger Volume
	if (GetTotalMassOfActorsOnPlate() > 40.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	} else if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	// find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// iterate through them adding their masses
	for (AActor* actor : OverlappingActors) {
		UPrimitiveComponent* PrimitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>();
		TotalMass += PrimitiveComponent->GetMass();
	}

	return TotalMass;
}

