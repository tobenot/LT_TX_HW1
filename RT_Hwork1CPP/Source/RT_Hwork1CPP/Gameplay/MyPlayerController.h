// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MySaveGame.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RT_HWORK1CPP_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

	UFUNCTION(BlueprintCallable)
	void SaveGameMy();
	
	void SaveGameFinalLevel();

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//UWidget* CoinWidget;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMySaveGame> SaveGameClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInfo")
		FName FirstLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UMySaveGame* SaveGameRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CoinBankInit;

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
		void SetLevelGoalEvent(const FName LevelHeader,int Total, int Gold, int Silver);

	virtual void SetupInputComponent() override;
	void ActionMenu();
	void ActionQuitGame();
	void ActionResetLevel();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
