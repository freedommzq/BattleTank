// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	// TODO Get the world position where the crosshair intersect
	FVector HitLocation;
	if (!GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController AimTowardsCrosshair: the crosshair hit nothing."));
	}
	else {
		// then, if it hits the landscape, control tank to aim at this point
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController AimTowardsCrosshair: the crosshair hit at %s."), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto tank_t = GetControlledTank();
	if (!tank_t) {
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController BeginPlay: can't get controlled tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay: %s"), *tank_t->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}
