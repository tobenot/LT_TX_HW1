// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RT_HWORK1CPP_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CoinBank;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName CurrentLevel;
};
