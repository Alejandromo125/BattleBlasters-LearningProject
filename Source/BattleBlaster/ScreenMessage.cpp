// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"

void UScreenMessage::SetMessageText(FString message)
{
	FText textToSend = FText::FromString(message);
	messageTextBlock->SetText(textToSend);
}
