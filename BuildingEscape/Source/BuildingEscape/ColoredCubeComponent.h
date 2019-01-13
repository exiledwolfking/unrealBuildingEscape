// Copyright Kyle Wahl 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ColoredCubeComponent.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UColoredCubeComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="10", UIMin="0", UIMax="10"))
		int clicksNeeded = 5;

	UPROPERTY(EditAnywhere)
		TArray<USoundCue*> NumberSoundCues;

	int clicks = 0;

public: 

	void Click();

	void ClearClicks();

	bool AreClicksCorrect();
	
};
