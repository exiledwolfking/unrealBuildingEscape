// Copyright Kyle Wahl 2018

#include "TrackerCube.h"



TEnumAsByte<cubetype::CubeType> UTrackerCube::GetType() {
	return type;
}

bool UTrackerCube::GetOpenDoor() {
	return OpenDoor;
}

void UTrackerCube::Click() {
	if (type == cubetype::CubeType::OPENDOOR) {
		bool ShouldOpenDoor = true;
		for (AStaticMeshActor* Cube : Cubes) {
			UColoredCubeComponent* ColoredCube = Cube->FindComponentByClass<UColoredCubeComponent>();
			if (ColoredCube && !ColoredCube->AreClicksCorrect()) {
				ShouldOpenDoor = false;
			}
		}

		OpenDoor = ShouldOpenDoor;
	}
	else if (type == cubetype::CubeType::RESET) {
		// reset counts on attached cubes
		for (AStaticMeshActor* Cube : Cubes) {
			UColoredCubeComponent* ColoredCube = Cube->FindComponentByClass<UColoredCubeComponent>();
			if (ColoredCube) {
				ColoredCube->ClearClicks();
			}
		}
	}
}