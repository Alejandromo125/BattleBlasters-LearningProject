// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "projectile.generated.h"

UCLASS()
class BATTLEBLASTER_API Aprojectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aprojectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* projectileMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* projectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* trailParticle;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* hitParticles;

	UPROPERTY(EditAnywhere)
	USoundBase* launchSound;

	UPROPERTY(EditAnywhere)
	USoundBase* hitSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> hitCameraShakeClass;

	UPROPERTY(EditAnywhere)
	float damage = 25.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);	

};
