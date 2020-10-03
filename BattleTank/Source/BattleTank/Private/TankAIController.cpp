// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
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
	if (!ensure(GetControlledTank() && GetPlayerTank())) {
		return;
	}

	MoveToActor(GetPlayerTank(), MaxFireRange);

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	//GetControlledTank()->Fire();
}
