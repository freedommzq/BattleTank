// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "TankAimingComponent.h"

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) {
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		// then, if it hits the landscape, control tank to aim at this point
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (ensure(AimingComponent)) {
			AimingComponent->AimAt(HitLocation);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Get HitLocation failed!"));	
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrossHairPosition = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// de-project the screen position of the crosshair to the world direction
	FVector LookDirection;	
	if (!GetLookDirection(CrossHairPosition, LookDirection)) {
		return false;
	}
	else {
		// line trace along the look direction
		if (!GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			return false;
		}
	}	

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenPosition, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; // this variable is ignored currently since it is useless

	return DeprojectScreenPositionToWorld(
		ScreenPosition.X,
		ScreenPosition.Y,
		CameraWorldLocation,
		OutLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResultTemp;
	auto StartPositon = PlayerCameraManager->GetCameraLocation();
	auto EndPosition = StartPositon + LookDirection * LineTraceRange;

	auto IsGetSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResultTemp,
		StartPositon,
		EndPosition,
		ECC_Visibility
	);

	if (!IsGetSuccess) {
		return false;
	}

	OutHitLocation = HitResultTemp.Location;

	return true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}
