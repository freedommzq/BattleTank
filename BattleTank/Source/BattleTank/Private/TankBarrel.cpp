// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto RelativeSpeedClamp = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);

	auto ElevationDegrees = RelativeSpeedClamp * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevationDegrees = RelativeRotation.Pitch + ElevationDegrees;

	auto NewElevationDegreesClamp = FMath::Clamp<float>(NewElevationDegrees, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewElevationDegreesClamp, 0, 0));
}
