// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectPawn.h"
#include "Tank.h"

#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATower : public ABaseProjectPawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank* tank;

	UPROPERTY(EditAnywhere)
	float fireRange = 700.f;

	UPROPERTY(EditAnywhere)
	float fireRate = 2.f;

	void CheckFireCondition();

	bool IsInFireRange();

	void HandleDestruction();
};
