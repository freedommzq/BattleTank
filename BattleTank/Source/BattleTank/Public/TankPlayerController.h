// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend class ATankAIController;
public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
	// moving the barrel so that shot would hit where the crosshair intersect the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenPosition, FVector& OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000; // unreal use centimeter as unit
};
