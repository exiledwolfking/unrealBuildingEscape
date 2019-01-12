// Copyright Kyle Wahl 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ColoredCubeComponent.generated.h"



UCLASS()
class BUILDINGESCAPE_API UColoredCubeComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	


	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="10", UIMin="0", UIMax="10"))
		int clicksNeeded = 5;

	UWorld* world = nullptr;

	int clicks = 0;

public: 

	void Click();

	void ClearClicks();

	bool AreClicksCorrect();
	
};
