// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "MyGameStateBase.h"
#include "Internationalization/Text.h"
#include "../Gameplay/MyLevelInfoHolder.h"

// Sets default values
AMyLevelInfoHolder::AMyLevelInfoHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComp"));
	TextComp->SetupAttachment(RootComponent);

	
}
void AMyLevelInfoHolder::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	FFormatNamedArguments Args;
	Args.Add("H", FText::FromName(LevelHeader));
	Args.Add("1", CoinGoal_Total);
	Args.Add("2", CoinGoal_Gold);
	Args.Add("3", CoinGoal_Silver);
	TextComp->SetText(FText::Format(NSLOCTEXT("Robert", "ExampleFText", "LevelHeader:  {H}\nTotal: {1}\nGold : {2}\nSilver: {3}\n"), Args));
}

	
// Called when the game starts or when spawned
void AMyLevelInfoHolder::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	float delayTime = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
			if (PlayerController) {
				PlayerController->SetLevelGoalEvent(LevelHeader, CoinGoal_Total, CoinGoal_Gold, CoinGoal_Silver);
			}
		}, delayTime, false);
	
	AMyGameStateBase* GameState = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(this));
	if (GameState) {
		GameState->SetCoinGoal(CoinGoal_Total, CoinGoal_Gold, CoinGoal_Silver);
	}
}

// Called every frame
void AMyLevelInfoHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

