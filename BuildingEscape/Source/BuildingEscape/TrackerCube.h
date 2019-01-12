// Copyright Kyle Wahl 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ColoredCubeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TrackerCube.generated.h"


/**
 *
 */
UENUM()
namespace cubetype {
	enum CubeType {
		OPENDOOR	UMETA(DisplayName = "OpenDoor"),
		RESET		UMETA(DisplayName = "Reset")
	};
}

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API UTrackerCube : public UStaticMeshComponent
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TEnumAsByte<cubetype::CubeType> type;

	// used to reference colored cubes to reset and check counts
	UPROPERTY(EditAnywhere)
		TArray<AStaticMeshActor*> Cubes;

	TEnumAsByte<cubetype::CubeType> GetType();

	bool OpenDoor = false;
	
public:

	bool GetOpenDoor();

	void ActorClick();

};
