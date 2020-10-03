// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto IntendVector = MoveVelocity.GetSafeNormal();
	auto ForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto MoveThrow = FVector::DotProduct(IntendVector, ForwardVector);
	IntendMoveForward(MoveThrow);

	//auto TurnThrow = FVector::CrossProduct(IntendVector, ForwardVector).Z;
	auto TurnThrow = FVector::CrossProduct(ForwardVector, IntendVector).Z;
	IntendTurnRight(TurnThrow);
}
