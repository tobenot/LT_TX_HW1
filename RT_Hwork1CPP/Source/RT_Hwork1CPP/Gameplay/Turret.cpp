// Fill out your copyright notice in the Description page of Project Settings.


#include "../Gameplay/Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "../Gameplay/MyBlueprintFunctionLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	MeshCompBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompBase"));
	MeshCompBase->SetupAttachment(RootComponent);

	MeshCompTurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompTurretBase"));
	MeshCompTurretBase->SetupAttachment(MeshCompBase);
;
	
	MeshCompBarrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompBarrel"));
	MeshCompBarrel->SetupAttachment(MeshCompTurretBase);

	ShootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootArrow"));
	ShootArrow->SetupAttachment(MeshCompBarrel);

	AttackDistance = 2000.0f;
	CanShoot = 1;

}
/*void ATurret::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ColorMaterial = GetMatByMat(MyMat);
	if (ColorMaterial) {
		MeshCompBase->SetMaterial(0, ColorMaterial);
	}
	
}
*/


// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurret::Shoot, 0.2f, true, 1.0f);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MeshCompTurretBase) 
	{
		ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (PlayerPawn)
		{
			FVector StartLoc = MeshCompTurretBase->GetComponentLocation();
			FVector EndLoc = PlayerPawn->GetActorLocation();
			if (UKismetMathLibrary::Vector_Distance(StartLoc,EndLoc) < AttackDistance)
			{
				MeshCompTurretBase->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(StartLoc, EndLoc));
			}

		}
		
	}



}
void ATurret::Shoot()
{
	if (CanShoot)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			if (SpawnBulletClass)
			{
				FVector Loc = ShootArrow->GetComponentLocation();
				FRotator Rot = ShootArrow->GetComponentRotation();
				FVector Scale = ShootArrow->GetComponentScale();
				Rot.Add(FMath::RandRange(-10, 10), FMath::RandRange(-10, 10), 0);

				FTransform SpawnTransform(Rot, Loc, Scale);
				auto MyDeferredActor = Cast<ATurretBullet>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SpawnBulletClass, SpawnTransform));
				if (MyDeferredActor != nullptr)
				{
					MyDeferredActor->InitMat(MyMat);

					UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
				}

				//AActor* const BulletRef = World->SpawnActor<AActor>(SpawnBulletClass,FTransform(Rot, Loc, Scale));
			}
		}

	}
}

