// Copyright Kyle Wahl 2018

#include "ColoredCubeComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"

void UColoredCubeComponent::Click() {
	clicks++;
}

void UColoredCubeComponent::ClearClicks() {
	clicks = 0;
}

bool UColoredCubeComponent::AreClicksCorrect() {
	return clicks == clicksNeeded;
}
