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
	if (!PressurePlate && Type == doortype::DoorType::WEIGHTTRIGGER) {
		UE_LOG(LogTemp, Error, TEXT("Pressure plate not found on : %s"), *(Owner->GetName()));
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Type == doortype::DoorType::WEIGHTTRIGGER) {
		// Poll the triger Volume
		if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
			OnOpen.Broadcast();
		}
		else {
			OnClose.Broadcast();
		}
	}
	else if (Type == doortype::DoorType::CUBETRIGGER) {
		if (CanCubeOpenDoor()) {
			OnOpen.Broadcast();
		}
		else {
			OnClose.Broadcast();
		}
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	// find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// iterate through them adding their masses
	for (AActor* actor : OverlappingActors) {
		UPrimitiveComponent* PrimitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>();
		TotalMass += PrimitiveComponent->GetMass();
	}
	return TotalMass;
}

bool UOpenDoor::CanCubeOpenDoor() {
	if (OpenDoorCube) {
		return OpenDoorCube->GetOpenDoor();
	}
	return false;
}

