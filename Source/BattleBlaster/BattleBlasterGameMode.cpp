// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "BattleBlastersGameInstance.h"

void ABattleBlasterGameMode::BeginPlay()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	towerCount = Towers.Num();

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (playerPawn)
	{
		tank = Cast<ATank>(playerPawn);
		if (!tank)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode: Failed to find the tank actor"));
		}
		else
		{
			for(AActor* actorTower : Towers)
			{
				ATower* tower = Cast<ATower>(actorTower);
				if (tower)
				{
					tower->tank = tank;
				}
			}
		}
		
	}
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (playerController)
	{
		screenMessageWidget = CreateWidget<UScreenMessage>(playerController, ScreenMessageClass);
		if (screenMessageWidget)
		{
			screenMessageWidget->AddToPlayerScreen();
			screenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
	countDownSeconds = countDownDelay;
	GetWorldTimerManager().SetTimer(countDownTimerHandle, this, &ABattleBlasterGameMode::OnCountDownTimerTimeOut,
		1.0f, true);

}



void ABattleBlasterGameMode::ActorDied(AActor* deadActor)
{
	bool isGameOver = false;
	isVictory = false;
	if (deadActor == tank)
	{
		tank->HandleDestruction();
		isGameOver = true;
	}
	else
	{
		ATower* deadTower = Cast<ATower>(deadActor);
		if (deadTower)
		{
			deadTower->HandleDestruction();
			towerCount--;
			if (towerCount <= 0)
			{
				isGameOver = true;
				isVictory = true;
			}
		}
	}

	if (isGameOver)
	{
		FString gameOverString = isVictory ? "Victory!" : "Defeat :(";
		screenMessageWidget->SetVisibility(ESlateVisibility::Visible);

		screenMessageWidget->SetMessageText(gameOverString);
		FTimerHandle gameOverTimeHandle;

		GetWorldTimerManager().SetTimer(gameOverTimeHandle, this, &ABattleBlasterGameMode::OnGameOverTimeOut,
			GameOverDelay, false);
	}
}

void ABattleBlasterGameMode::OnCountDownTimerTimeOut()
{
	

	if (countDownSeconds > 0)
	{
		FString newString = FString::FromInt(countDownSeconds);
		screenMessageWidget->SetMessageText(newString);
	}
	else if (countDownSeconds == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("GO!"));
		screenMessageWidget->SetMessageText("GO!");
		tank->SetPlayerEnabled(true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(countDownTimerHandle);
		countDownSeconds = countDownDelay;
		screenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
		screenMessageWidget->SetMessageText("");

	}

	countDownSeconds--;
}

void ABattleBlasterGameMode::OnGameOverTimeOut()
{
	UGameInstance* gameInstance = GetGameInstance();
	if (gameInstance)
	{
		UBattleBlastersGameInstance* battleBlastersGameInstance = Cast<UBattleBlastersGameInstance>(gameInstance);
		if (battleBlastersGameInstance)
		{
			if (isVictory)
			{
				battleBlastersGameInstance->LoadNextLevel();
			}
			else
			{
				battleBlastersGameInstance->RestartCurrentLevel();
			}
		}
	}
	
}
