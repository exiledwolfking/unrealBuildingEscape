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
		// check that attached cubes have proper click amounts to open door
		bool ShouldOpenDoor = true;
		for (AStaticMeshActor* Cube : Cubes) {
			UColoredCubeComponent* ColoredCube = Cube->FindComponentByClass<UColoredCubeComponent>();
			if (ColoredCube && !ColoredCube->AreClicksCorrect()) {
				ShouldOpenDoor = false;
			}
		}

		OpenDoor = ShouldOpenDoor;
		if (OpenDoor && CodeAccepted) {
			UGameplayStatics::PlaySound2D(GetOwner(), CodeAccepted, 1.0F, 1.0F, 0.0F, nullptr, GetOwner());
		}
		else if (!OpenDoor && InvalidCode) {
			UGameplayStatics::PlaySound2D(GetOwner(), InvalidCode, 1.0F, 1.0F, 0.0F, nullptr, GetOwner());
		}
	}
	else if (type == cubetype::CubeType::RESET) {
		// reset counts on attached cubes
		for (AStaticMeshActor* Cube : Cubes) {
			UColoredCubeComponent* ColoredCube = Cube->FindComponentByClass<UColoredCubeComponent>();
			if (ColoredCube) {
				ColoredCube->ClearClicks();
			}
		}
		if (CubesReset) {
			UGameplayStatics::PlaySound2D(GetOwner(), CubesReset, 1.0F, 1.0F, 0.0F, nullptr, GetOwner());
		}
	}
}