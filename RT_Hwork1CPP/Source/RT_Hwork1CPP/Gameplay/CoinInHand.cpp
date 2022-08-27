// Fill out your copyright notice in the Description page of Project Settings.


#include "../Gameplay/CoinInHand.h"
#include "MyTCharacter.h"

// Sets default values
ACoinInHand::ACoinInHand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(RootComponent);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinInHand::SphereBeginOverlap);

}

UStaticMeshComponent* ACoinInHand::GetMeshComp() {
	return MeshComp;
}

void ACoinInHand::InitMat(int Mat)
{
	MyMat = Mat;
}
// Called when the game starts or when spawned
void ACoinInHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinInHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoinInHand::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyTCharacter* Pawn = Cast<AMyTCharacter>(OtherActor);
	if (Pawn)
	{
		if (!isHanding) {
			if (!(Pawn->MyCoinInHand)) {
				isHanding = 1;
				MeshComp->SetSimulatePhysics(false);
				MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				if (Pawn) {
					Pawn->PickCoinInHand(this);
				}
				else {
					MeshComp->SetSimulatePhysics(true);
					MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					isHanding = 0;
				}
			
			}
		}
	}
}

void ACoinInHand::ThrowCoin(FVector Impulse) {
	isHanding = 0;
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	if (MeshComp) {
		MeshComp->AddImpulse(Impulse, NAME_None,true);
	}
}

