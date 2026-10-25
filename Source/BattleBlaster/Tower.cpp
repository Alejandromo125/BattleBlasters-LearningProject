// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle fireTimerHandle;
	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &ATower::CheckFireCondition,fireRate,true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsInFireRange())
			RotateTurret(tank->GetActorLocation());
}

void ATower::CheckFireCondition()
{
	if(IsInFireRange())
		Fire();
		
}

bool ATower::IsInFireRange()
{
	if (tank && tank->isAlive)
		return (FVector::Dist(this->GetActorLocation(), tank->GetActorLocation()) <= fireRange);
		
	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	UE_LOG(LogTemp, Display, TEXT("HandleDestructionTower"));
	Destroy();
}
