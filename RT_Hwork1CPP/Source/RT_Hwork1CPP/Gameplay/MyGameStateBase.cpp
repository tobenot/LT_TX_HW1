// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../Gameplay/MyGameStateBase.h"

void AMyGameStateBase::CoinTest() {
	AMyTCharacter* PlayerPawn = Cast<AMyTCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerPawn) {
		if (PlayerPawn->CoinTotal >= CoinGoal_Total) {
			if (PlayerPawn->CoinGold >= CoinGoal_Gold) {
				if (PlayerPawn->CoinSilver >= CoinGoal_Silver) {
					LevelClear = 1;
				}
			}
		}
	}
}

void AMyGameStateBase::SetCoinGoal(int Total, int Gold, int Silver) {
	CoinGoal_Total = Total ;
	CoinGoal_Gold = Gold ;
	CoinGoal_Silver = Silver ;
}