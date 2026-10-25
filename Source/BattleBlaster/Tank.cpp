// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArmComp->SetupAttachment(capsuleComp);
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(springArmComp);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	playerController = Cast<APlayerController>(Controller);
	if (playerController)
	{
		if (ULocalPlayer* localPlayer = playerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer))
			{
				Subsystem->AddMappingContext(defaultMappingContext, 0);
			}
		}
	}

	SetPlayerEnabled(false);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerController = Cast<APlayerController>(Controller);
	if (playerController)
	{
		FHitResult hitResult;
		playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
		RotateTurret(hitResult.ImpactPoint);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(moveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EIC->BindAction(rotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
		EIC->BindAction(fireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

void ATank::MoveInput(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();
	FVector DeltaLocation = FVector(0.f, 0.f, 0.f);
	DeltaLocation.X = speed * inputValue * GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::RotateInput(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();
	FRotator deltaRotation = FRotator(0.f, 0.f, 0.f);
	deltaRotation.Yaw = rotationDegrees * inputValue * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(deltaRotation, true);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	UE_LOG(LogTemp, Display, TEXT("HandleTankDestruction"));
	if (deathCameraShakeClass)
	{
		playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (playerController)
		{
			playerController->ClientStartCameraShake(deathCameraShakeClass);
		}
	}
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
	isAlive = false;
}

void ATank::SetPlayerEnabled(bool enabled)
{
	if (playerController)
	{
		if (enabled)
		{
			EnableInput(playerController);
		}
		else
		{
			DisableInput(playerController);
		}
		playerController->SetShowMouseCursor(enabled);
	}
}
