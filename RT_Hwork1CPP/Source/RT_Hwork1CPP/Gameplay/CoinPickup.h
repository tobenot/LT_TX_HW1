// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "CoinInHand.h"
#include "CoinPickup.generated.h"

UCLASS()
class RT_HWORK1CPP_API ACoinPickup : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* SphereComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		URotatingMovementComponent* RotatingMovement;


public:	
	// Sets default values for this actor's properties
	ACoinPickup();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MyMat;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACoinInHand> SpawnCoinClass;
	*/
	//UClass* SpawnCoinClass;
		/** Projectile class to spawn */
	/*UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ACoinInHand> SpawnCoinClass;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ACoinInHand> SpawnCoinClass2;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AActor> BlueprintVar;*/

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACoinInHand> SpawnCoinClass;

	void PickUpCheck(AActor* OtherActor);

	UFUNCTION()
	void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnCoinInHand(FTransform PawnTransform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
