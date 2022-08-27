// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinInHand.h"
#include "../Gameplay/WallBox.h"

// Sets default values
AWallBox::AWallBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WallBoxSceneComponent"));
	}*/

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
		CollisionComponent->InitBoxExtent(FVector(256, 256, 256));
		RootComponent = CollisionComponent;
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWallBox::BoxBeginOverlap);
	}


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWallBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallBox::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DesFlag)
	{
		if (OtherActor)
		{
			ACoinInHand* OverlapThing = Cast<ACoinInHand>(OtherActor);
			if (OverlapThing)
			{
				if (!OverlapThing->isHanding)
				{
					if (MyMat == OverlapThing->MyMat)
					{
						OverlapThing->Destroy();
						DesFlag = 1;
						DesWallBoxEvent();
					}
				}
			}
		}
	}
	
}