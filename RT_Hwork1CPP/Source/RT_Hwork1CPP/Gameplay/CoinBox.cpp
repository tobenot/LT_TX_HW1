// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretBullet.h"
#include "CoinInHand.h"
#include "Kismet/GameplayStatics.h"
#include "MyTCharacter.h"
#include "MyGameInstance.h"
#include "MyGameStateBase.h"
#include "../Gameplay/CoinBox.h"


// Sets default values
ACoinBox::ACoinBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(Root);
	//RootComponent = Root;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinBox::SphereBeginOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ACoinBox::SphereHit);
	//碰撞为什么检测不到
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(RootComponent);



	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinBox::BoxBeginOverlap);
}

// Called when the game starts or when spawned
void ACoinBox::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoinBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinBox::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		CheckCoin(OtherActor);
	}
	
	
}
void ACoinBox::SphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor) 
	{
		CheckCoin(OtherActor);
	}

}

void ACoinBox::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATurretBullet* OverlapBullet = Cast<ATurretBullet>(OtherActor);
		if (OverlapBullet) {
			OverlapBullet->GoBack();
		}
	}
}

void ACoinBox::CheckCoin(AActor* OtherActor)
{
	if (OtherActor) 
	{
		ACoinInHand* OtherActorCast = Cast<ACoinInHand>(OtherActor);
		if (OtherActorCast) 
		{
			if (!(OtherActorCast->isHanding)) 
			{
				if (OtherActorCast->MyMat == MyMat) 
				{
					if (!isFeed) 
					{
						isFeed = 1;
						OtherActorCast->Destroy();
						AMyTCharacter* PlayerPawn = Cast<AMyTCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
						if(PlayerPawn)
						{
							switch (MyMat) 
							{
								case 0:
									PlayerPawn->CoinGold = PlayerPawn->CoinGold + 1;
									break;
								case 1:
									PlayerPawn->CoinSilver = PlayerPawn->CoinSilver + 1;
									break;
								default:break;
							}
							PlayerPawn->CoinTotal = PlayerPawn->CoinTotal + 1;
						}
						UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
						if (GameInstance) 
						{
							GameInstance->CoinBank = GameInstance->CoinBank + (MyMat == 0 ? 10 : (MyMat == 1 ? 1 : (MyMat == 3 ? 10000 : 0)));
						}

						AMyGameStateBase* GameState = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(this));
						if (GameState) 
						{
							//GameState->CoinTest();
						}

						SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						FeedCoinEvent();
					}
				}
			}
		}
	}

}

//void ACoinBox::FeedCoinEvent() {}