// Fill out your copyright notice in the Description page of Project Settings.


#include "projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Aprojectile::Aprojectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	projectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileComponent"));
	SetRootComponent(projectileMeshComponent);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

	trailParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailParticlesComponent"));
	trailParticle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void Aprojectile::BeginPlay()
{
	Super::BeginPlay();
	projectileMeshComponent->OnComponentHit.AddDynamic(this, &Aprojectile::OnHit);
	if (launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), launchSound, GetActorLocation());

	}
}

// Called every frame
void Aprojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aprojectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* myOwner = GetOwner();
	if (myOwner)
	{
		if (OtherActor && OtherActor != myOwner && OtherActor != this)
		{
			UGameplayStatics::ApplyDamage(OtherActor, damage, myOwner->GetInstigatorController(), 
				this, UDamageType::StaticClass());
			
		}
		if (hitParticles)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitParticles, GetActorLocation(), GetActorRotation());
		}
		if (launchSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), launchSound, GetActorLocation());
		}
		if (hitCameraShakeClass)
		{
			APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (playerController)
			{
				playerController->ClientStartCameraShake(hitCameraShakeClass);
			}
		}
	}
	Destroy();
}


