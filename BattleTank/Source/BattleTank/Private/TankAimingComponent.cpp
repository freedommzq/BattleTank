// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::Init(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) {	
		return;
	}

	if (!ensure(Turret)) {
		return;
	}

	FVector OutLaunchVelocity;

	// TODO This function will show some weird warning
	auto IsSuccess = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (IsSuccess){
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretTowards();
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileClass)) {
		return;
	}

	if (FiringStatus == EFiringStatus::Reloading || FiringStatus == EFiringStatus::OutOfAmmo) {
		return;
	}

	if (!ensure(Barrel)) {
		return;
	}

	auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, ProjectileRotation);

	if (ensure(Projectile)) {
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		--AmmoCount;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoCount <= 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
		return;
	}

	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!IsReloaded) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{	
	if (!ensure(Barrel)) {
		return;
	}

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards()
{
	if (!ensure(Turret)) {
		return;
	}

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	if (FMath::Abs(DeltaRotator.Yaw) > 180.0) {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(DeltaRotator.Yaw);	
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) {
		return false;
	}

	auto BarrelForward = Barrel->GetForwardVector().GetSafeNormal();
	return !BarrelForward.Equals(AimDirection, 0.01);
}
