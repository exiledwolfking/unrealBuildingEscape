// Copyright Kyle Wahl 2018

#include "ColoredCubeComponent.h"
#include "Engine/World.h"
#include <string>
#include "Engine/StaticMesh.h"
using namespace std;

void UColoredCubeComponent::Click() {
	if (clicks < 10) {
		clicks++;
	}
	if (NumberSoundCues.Num() >= clicks) {
		UGameplayStatics::PlaySound2D(GetOwner(), NumberSoundCues[clicks - 1], 1.0F, 1.0F, 0.0F, nullptr, GetOwner());
	}
}

void UColoredCubeComponent::ClearClicks() {
	clicks = 0;
}

bool UColoredCubeComponent::AreClicksCorrect() {
	return clicks == clicksNeeded;
}
