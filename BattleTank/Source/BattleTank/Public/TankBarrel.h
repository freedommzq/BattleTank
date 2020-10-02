// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed); // give a relative value between -1.0 - 1.0

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = 0.0;
};
