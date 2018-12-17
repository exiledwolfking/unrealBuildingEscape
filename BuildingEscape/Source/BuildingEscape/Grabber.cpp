// Copyright Kyle Wahl 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Owner = GetOwner();
	UWorld* world = GetWorld();

	PlayerController = world->GetFirstPlayerController();

	FindPhysicsHandleComponent();

	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// physics handle is found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	/// look for attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Log, TEXT("Input Component found on %s"), *GetOwner()->GetName());

		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input Component not found on %s"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get player view point this tick
	FVector location;
	FRotator rotation;
	PlayerController->GetPlayerViewPoint(location, rotation);
	// UE_LOG(LogTemp, Warning, TEXT("%s --- %s"), *(location.ToString()), *(rotation.ToString()));

	FVector LineTraceDirection = (rotation.Vector() * this->Reach);
	FVector LineTraceEnd = location + LineTraceDirection;

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line trace (ray cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	// See what we hit
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *(HitActor->GetName()));
	}
	return FHitResult();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
		// move the object that we're holding



}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	/// try and reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	/// if we hit something then attach a physics handle

	// todo attach physics handle
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release pressed"));

	// release physics handle
}