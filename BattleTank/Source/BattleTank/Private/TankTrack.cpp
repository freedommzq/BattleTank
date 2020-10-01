// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s throttle is %f!"), *GetName(), Throttle);

	// TODO clamp the Throttle between -1.0 to 1.0

	auto Force = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	//ForceLocation = FVector(ForceLocation.X, ForceLocation.Y, ForceLocation.Z + 100.0);
	auto TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankBody->AddForceAtLocation(Force, ForceLocation);
}