// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "MyGameInstance.h"
#include "Components/InputComponent.h"
#include "../Gameplay/MyPlayerController.h"
AMyPlayerController::AMyPlayerController() {
	FirstLevelName = FName("Level_00");

	//UI在蓝图创建！

}
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (SaveGameClass) {
		SaveGameRef = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
		SaveGameMy();
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (GameInstance) {
			CoinBankInit = GameInstance->CoinBank;
		}
	}
	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Menu", IE_Pressed, this, &AMyPlayerController::ActionMenu);
	InputComponent->BindAction("QuitGame", IE_Pressed, this, &AMyPlayerController::ActionQuitGame);
	InputComponent->BindAction("ResetLevel", IE_Pressed, this, &AMyPlayerController::ActionResetLevel);
}
void AMyPlayerController::ActionMenu() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Please press Q to quit game!"));
}
void AMyPlayerController::ActionQuitGame() {
	UKismetSystemLibrary::QuitGame(this,this,EQuitPreference::Quit,false);
}
void AMyPlayerController::ActionResetLevel() {
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance) {
		GameInstance->CoinBank = CoinBankInit;
		UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
		//上面的做法不会重置关卡，没有效果
		//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

void AMyPlayerController::SaveGameMy() {
	if (SaveGameRef) {
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (GameInstance) {
			SaveGameRef->CoinBank = GameInstance->CoinBank;
			SaveGameRef->CurrentLevel = FName(UGameplayStatics::GetCurrentLevelName(this));
			UGameplayStatics::SaveGameToSlot(SaveGameRef, "A", 0);
		}
	}
	
}

void AMyPlayerController::SaveGameFinalLevel() {
	if (SaveGameRef) {
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (GameInstance) {
			SaveGameRef->CoinBank = GameInstance->CoinBank;
			SaveGameRef->CurrentLevel = FirstLevelName;
			UGameplayStatics::SaveGameToSlot(SaveGameRef, "A", 0);
		}
	}

}
