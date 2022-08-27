// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class RT_HWORK1CPP_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool LevelClear;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CoinGoal_Total;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CoinGoal_Gold;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CoinGoal_Silver;

	UFUNCTION(BlueprintCallable)
	void CoinTest();
	UFUNCTION(BlueprintCallable)
		void SetCoinGoal(int Total,int Gold,int Silver);
};
