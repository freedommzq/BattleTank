// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) {
		return;
	}

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!IsReloaded) {
		return;
	}
	else {
		LastFireTime = FPlatformTime::Seconds();
	}
	
	if (!Barrel) {
		return;
	}

	auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, ProjectileRotation);

	if (Projectile) {
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

