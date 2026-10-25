// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectPawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABaseProjectPawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputMappingContext* defaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* moveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* rotateAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* fireAction;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComponent;

	void MoveInput(const FInputActionValue& value);
	void RotateInput(const FInputActionValue& value);


	UPROPERTY(EditAnywhere)
	float speed = 300.f;
	UPROPERTY(EditAnywhere)
	float rotationDegrees = 100.f;

	bool isAlive = true;

	APlayerController* playerController;

	void HandleDestruction();

	void SetPlayerEnabled(bool enabled);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> deathCameraShakeClass;
};
