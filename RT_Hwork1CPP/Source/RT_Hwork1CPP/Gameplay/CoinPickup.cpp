// Fill out your copyright notice in the Description page of Project Settings.


#include "../Gameplay/CoinPickup.h"
#include "MyTCharacter.h"
#include "CoinInHand.h"
#include "Kismet/GameplayStatics.h"
#include <RT_Hwork1CPP/Gameplay/MyBlueprintFunctionLibrary.cpp>

// Sets default values
//#include <RT_Hwork1CPP/Gameplay/CoinInHand.h>

ACoinPickup::ACoinPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;
	//Root->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SetRootComponent(Root);
	RootComponent = Root;
	//Root->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//RootComponent = StaticMesh;
	StaticMesh->SetupAttachment(RootComponent);
	

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::SphereBeginOverlap);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	//RotatingMovement->SetupAttachment(RootComponent);

	//ColorMaterial = GetMatByMat(MyMat);

	//SpawnCoinClass = StaticLoadClass(ACoinInHand::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprints/BP_CoinInHand.BP_CoinInHand'"));
	//SpawnCoinClass = LoadObject< UClass >(nullptr, TEXT("Blueprint'/Game/Blueprints/BP_CoinInHand.BP_CoinInHand_C'"));
	/*static ConstructorHelpers::FObjectFinder<UBlueprint>FindObject(TEXT("Blueprint'/Game/Blueprints/BP_CoinInHand.BP_CoinInHand'"));
	if (FindObject.Object)
	{
		SpawnCoinClass = (UClass*)FindObject.Object->GeneratedClass;
	}*/

	/*static ConstructorHelpers::FObjectFinder<UBlueprint>FindObject(TEXT("Blueprint'/Game/Blueprints/BP_CoinInHand.BP_CoinInHand'"));//这条是不使用蓝图确定生成实例类型时使用的
	if (FindObject.Object)
	{
		BlueprintVar = (UClass*)FindObject.Object->GeneratedClass;
	}*/
}

// Called when the game starts or when spawned
void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();
	
	RotatingMovement->RotationRate.Add(0,FMath::RandRange(-90,90),0);
}

// Called every frame
void ACoinPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACoinPickup::PickUpCheck(AActor* OtherActor)
{
	if (OtherActor)
	{
		AMyTCharacter* Pawn = Cast<AMyTCharacter>(OtherActor);
		if (Pawn)
		{
			if (!(Pawn->MyCoinInHand)) {
				/*FTransform PawnTransform = Pawn->GetActorTransform();
				//FVector PLocation = Pawn->GetActorLocation;
				//FRotator PRotation = Pawn->GetActorRotation;
				UWorld* World = GetWorld();
				if (World)
				{
					if (SpawnCoinClass2) {
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = Pawn;
						SpawnParams.Instigator = GetInstigator();
						//World->SpawnActor<ACoinInHand>(ACoinInHand::StaticClass(), PawnTransform, SpawnParams);
						/*World->SpawnActor<AActor>(SpawnCoinClass, PawnTransform, SpawnParams);
						if (GEngine) {
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, SpawnCoinClass->GetPathName());
						}*/

						/*if (IsValid(SpawnCoinClass))
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, SpawnCoinClass2->GetPathName());
							World->SpawnActor<ACoinInHand >(SpawnCoinClass2, GetActorTransform());
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, SpawnCoinClass2->GetPathName());
						}
					}
					
				}*/

				/*if (SpawnCoinClass2 != nullptr)
				{
					UWorld* const World = GetWorld();
					if (World != nullptr)
					{
						World->SpawnActor<ACoinInHand>(SpawnCoinClass, GetActorTransform());
						//World->SpawnActor<ACPPFirstTempProjectile>(ProjectileClass, GetActorTransform());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, SpawnCoinClass2->GetPathName());
					}
				}*/
				SpawnCoinInHand(Pawn->GetActorTransform());
				Destroy();
			}
		}
	}

}
void ACoinPickup::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		PickUpCheck(OtherActor);
	}

}

void ACoinPickup::SpawnCoinInHand(FTransform PawnTransform) {
	/*
	//不传参的可行生成方案
	UWorld* const World = GetWorld();
	if (World) {
		if (SpawnCoinClass) {
			AActor* const CoinRef = World->SpawnActor<AActor>(SpawnCoinClass, PawnTransform);
		}
	}*/
	
	auto MyDeferredActor = Cast<ACoinInHand>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SpawnCoinClass, PawnTransform));
	if (MyDeferredActor != nullptr)
	{
		MyDeferredActor->InitMat(MyMat);
		UGameplayStatics::FinishSpawningActor(MyDeferredActor, PawnTransform);
	}


}