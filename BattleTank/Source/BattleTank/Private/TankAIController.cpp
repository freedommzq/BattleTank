// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ReactToPlayer();
}

void ATankAIController::ReactToPlayer()
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(GetPawn() && PlayerPawn)) {
		return;
	}

	MoveToActor(PlayerPawn, MaxFireRange);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		AimingComponent->AimAt(PlayerPawn->GetActorLocation());
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
			//AimingComponent->Fire();		
		}
	}
}
