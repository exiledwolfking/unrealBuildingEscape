// Copyright Kyle Wahl 2018

#include "ColoredCubeComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"

void UColoredCubeComponent::Click() {
	clicks++;
	UE_LOG(LogTemp, Warning, TEXT("Clicks : %d"), clicks);
}

void UColoredCubeComponent::ClearClicks() {
	clicks = 0;
}

bool UColoredCubeComponent::AreClicksCorrect() {
	return clicks == clicksNeeded;
}
