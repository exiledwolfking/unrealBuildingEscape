// Copyright Kyle Wahl 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ColoredCubeComponent.h"
#include "Sound/SoundCue.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UTrackerCube : public UStaticMeshComponent
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	TEnumAsByte<cubetype::CubeType> type;

	// used to reference colored cubes to reset and check counts
	UPROPERTY(EditAnywhere)
		TArray<AStaticMeshActor*> Cubes;

	UPROPERTY(EditAnywhere)
		USoundCue* CodeAccepted;

	UPROPERTY(EditAnywhere)
		USoundCue* CubesReset;

	UPROPERTY(EditAnywhere)
		USoundCue* InvalidCode;

	bool OpenDoor = false;
	
public:
	TEnumAsByte<cubetype::CubeType> GetType();

	bool GetOpenDoor();

	void Click();

};
