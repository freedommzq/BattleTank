// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// If not press control button, the throttle input will be 0, so can't override throttle directly
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0, 1.0);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();

	// reset throttle
	CurrentThrottle = 0.0;
}

void UTankTrack::DriveTrack()
{
	auto Force = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankBody->AddForceAtLocation(Force, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectForce = (TankRoot->GetMass() * CorrectAcceleration) / 2; // since there are 2 tracks
	TankRoot->AddForce(CorrectForce);
}