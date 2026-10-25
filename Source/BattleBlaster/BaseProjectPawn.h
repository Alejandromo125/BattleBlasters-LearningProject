// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "projectile.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "BaseProjectPawn.generated.h"

UCLASS()
class BATTLEBLASTER_API ABaseProjectPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseProjectPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* capsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<Aprojectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* deathParticles;
	

	UPROPERTY(EditAnywhere)
	USoundBase* deathSound;

	void RotateTurret(FVector lookAtTarget);

	void Fire();

	void HandleDestruction();
};
