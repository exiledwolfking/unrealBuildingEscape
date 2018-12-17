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
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	/// look for attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
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

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line trace (ray cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	// See what we hit
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *(HitActor->GetName()));
	}
	return Hit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LineTraceEnd = GetLineTraceEnd();

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	/// try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();

	auto ActorHit = HitResult.GetActor();

	// if we hit something then attach a physics handle
	if (ActorHit) {
		// attach physics handle
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation());
	}


}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release pressed"));

	// release physics handle
	PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetLineTraceStart() {

	FVector location;
	FRotator rotation;
	PlayerController->GetPlayerViewPoint(location, rotation);

	return location;

}

FVector UGrabber::GetLineTraceEnd() {

	FVector location;
	FRotator rotation;
	PlayerController->GetPlayerViewPoint(location, rotation);

	FVector LineTraceDirection = (rotation.Vector() * this->Reach);
	return location + LineTraceDirection;

}