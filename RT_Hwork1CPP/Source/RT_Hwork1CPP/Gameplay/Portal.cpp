// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameStateBase.h"
#include "MyPlayerController.h"
#include "../Gameplay/Portal.h"

// Sets default values
APortal::APortal()
{
	MainMenuLevelName = FName("Level_MainMenu");
	NextLevel = FName("Level_");
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(RootComponent);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->SetSphereRadius(128.0);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::SphereBeginOverlap);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(90, 0, 0);
	RotatingMovement->PivotTranslation = FVector(0, 0, 180);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyTCharacter* Pawn = Cast<AMyTCharacter>(OtherActor);
	if (Pawn)
	{
		AMyGameStateBase* GameState = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(this));
		if (GameState) {
			GameState->CoinTest();
			if (GameState->LevelClear) {
				AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
				if (PlayerController) {
					//if (MainMenuLevelName.IsEqual(FName(UGameplayStatics::GetCurrentLevelName(this)))) {
					if (MainMenuLevelName.IsEqual(NextLevel))
					{
						PlayerController->SaveGameFinalLevel();
					}
					else {
						PlayerController->SaveGameMy();
					}
					FTimerHandle TimerHandle;
					float delayTime = 0.5f;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
						{
							UGameplayStatics::SetGlobalTimeDilation(this,0.1f);
							float delayTime = 0.1f;
							GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
								{
									UGameplayStatics::OpenLevel(this,NextLevel);

								}, delayTime, false);
						}, delayTime, false);


				}
			}
		}
	}
}