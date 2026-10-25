// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlastersGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBattleBlastersGameInstance::ChangeLevel(int32 index)
{
	if (index > 0 && index <= lastLevelIndex)
	{
		currentLevelIndex = index;
		FString currentLevelName = FString::Printf(TEXT("Level_%d"), currentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *currentLevelName);
	}
}
void UBattleBlastersGameInstance::LoadNextLevel()
{
	if (currentLevelIndex < lastLevelIndex)
	{
		ChangeLevel(currentLevelIndex + 1);
	}
	else
	{
		RestartGame();
	}
}
void UBattleBlastersGameInstance::RestartCurrentLevel()
{
	ChangeLevel(currentLevelIndex);
}
void UBattleBlastersGameInstance::RestartGame()
{
	ChangeLevel(1);
}