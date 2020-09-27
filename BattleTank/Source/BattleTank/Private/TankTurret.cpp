// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto RelativeSpeedClamp = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);

	auto RotateDegrees = RelativeSpeedClamp * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotateDegrees = GetRelativeRotation().Yaw + RotateDegrees;

	SetRelativeRotation(FRotator(0, NewRotateDegrees, 0));
}
