// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto tank_t = GetControlledTank();
	if (!tank_t) {
		UE_LOG(LogTemp, Error, TEXT("Controller BeginPlay: can't get controlled tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controller BeginPlay: %s"), *tank_t->GetName())	
	}

}
