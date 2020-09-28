// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto aiTank_t = GetControlledTank();
	if (!aiTank_t) {
		UE_LOG(LogTemp, Error, TEXT("AITank not found!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AITank: %s"), *aiTank_t->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ReactToPlayer();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto pc_t = GetWorld()->GetFirstPlayerController();
	if (!pc_t) {
		return nullptr;
	}

	auto tpc_t = Cast<ATankPlayerController>(pc_t);
	if (!tpc_t) {
		return nullptr;
	}

	return tpc_t->GetControlledTank();
}

void ATankAIController::ReactToPlayer()
{
	if (!GetControlledTank() || !GetPlayerTank()) {
		return;
	}

	// aim at the player
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	// TODO if out of range, move towards the player

	// TODO fire if ready
	GetControlledTank()->Fire();
}
