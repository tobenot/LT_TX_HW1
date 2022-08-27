// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "TurretBullet.h"
#include "Turret.generated.h"

UCLASS()
class RT_HWORK1CPP_API ATurret : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ATurret();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshCompBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshCompTurretBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshCompBarrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UArrowComponent* ShootArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class ATurretBullet> SpawnBulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MyMat;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	UMaterial* ColorMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanShoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackDistance;

	UFUNCTION()
		void Shoot();
	
	//void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
