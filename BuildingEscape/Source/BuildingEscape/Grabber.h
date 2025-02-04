// Copyright Kyle Wahl 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColoredCubeComponent.h"
#include "TrackerCube.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:	

	AActor* Owner;
	APlayerController* PlayerController;
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Ray cast and grab what's in reach
	void Grab();
	void Release();

	FVector GetLineTraceStart();

	FVector GetLineTraceEnd();

	void FindPhysicsHandleComponent();

	void SetupInputComponent();

	// return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// return hit for first static body in reach
	const FHitResult GetFirstStaticBodyInReach();

};
