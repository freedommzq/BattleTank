// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) {
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		// then, if it hits the landscape, control tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Get HitLocation failed!"));	
	//}
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

	auto playerTank_t = GetControlledTank();
	if (!playerTank_t) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank not found!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank: %s"), *playerTank_t->GetName());
	}

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank %s not found its Aiming Component!"), *playerTank_t->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}
