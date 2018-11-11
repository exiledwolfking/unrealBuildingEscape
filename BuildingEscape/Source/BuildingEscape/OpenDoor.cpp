// Copyright Kyle Wahl 2018

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	ActorThatOpens = world->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	AActor* owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, 90.0f, 0.0f);
	owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor* owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, 0.0f, 0.0f);
	owner->SetActorRotation(newRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the triger Volume
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	} else {
		CloseDoor();
	}
	// If the ActorThatOpens is in the volume, then open the door
}

