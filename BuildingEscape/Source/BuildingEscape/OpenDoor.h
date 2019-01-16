// Copyright Kyle Wahl 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrackerCube.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UENUM()
namespace doortype {
	enum DoorType {
		WEIGHTTRIGGER     UMETA(DisplayName = "Weight Trigger"), // first door triggered by weight trigger volume
		CUBETRIGGER       UMETA(DisplayName = "Cube Trigger") // second door triggered by a cubetype::CubeType::OPENDOOR cube
	};
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UOpenDoor();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		UPROPERTY(BluePrintAssignable)
		FDoorEvent OnOpen;

		UPROPERTY(BluePrintAssignable)
		FDoorEvent OnClose;

		UPROPERTY(EditAnywhere)
		TEnumAsByte<doortype::DoorType> Type;

	private:

		AActor* Owner = nullptr;

		UPROPERTY(EditAnywhere, Category="Set TriggerMass and PressurePlate for WEIGHTTRIGGER door type")
		float TriggerMass = 40.f;

		UPROPERTY(EditAnywhere, Category = "Set TriggerMass and PressurePlate for WEIGHTTRIGGER door type")
		ATriggerVolume* PressurePlate = nullptr;

		UPROPERTY(EditAnywhere, Category = "Set OpenDoorCube for CUBETRIGGER door type")
		AStaticMeshActor* OpenDoorCube = nullptr;

		UTrackerCube* TrackerCube = nullptr;

		bool CanCubeOpenDoor();

		float GetTotalMassOfActorsOnPlate();
};
