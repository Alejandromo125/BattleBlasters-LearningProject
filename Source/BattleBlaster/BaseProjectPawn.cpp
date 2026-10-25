// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectPawn.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABaseProjectPawn::ABaseProjectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(capsuleComp);

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	baseMesh->SetupAttachment(capsuleComp);


	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMeshComponent"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPointComponent"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

// Called when the game starts or when spawned
void ABaseProjectPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseProjectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseProjectPawn::RotateTurret(FVector lookAtTarget)
{
	FVector vectorTarget = lookAtTarget - turretMesh->GetComponentLocation();
	FRotator rotation = FRotator(0.f, vectorTarget.Rotation().Yaw, 0.f);
	FRotator interpolatedRotation = FMath::RInterpTo(turretMesh->GetComponentRotation(), rotation, GetWorld()->GetDeltaSeconds(), 10.f);
	turretMesh->SetWorldRotation(interpolatedRotation);
}

void ABaseProjectPawn::Fire()
{
	FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();

	Aprojectile* projectile = GetWorld()->SpawnActor<Aprojectile>(ProjectileClass, spawnLocation, spawnRotation);

	if (projectile)
	{
		projectile->SetOwner(this);
	}

}

void ABaseProjectPawn::HandleDestruction()
{
	UE_LOG(LogTemp, Display, TEXT("BasePawnHandleDestruction"));
	if (deathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), deathParticles, GetActorLocation(), GetActorRotation());
	}
	if (deathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), deathSound, GetActorLocation());
	}
}

