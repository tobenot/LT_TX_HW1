// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "CoinInHand.generated.h"

UCLASS()
class RT_HWORK1CPP_API ACoinInHand : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* SphereComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* Root;

public:	
	// Sets default values for this actor's properties
	ACoinInHand();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int MyMat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isHanding;
	void ThrowCoin(FVector Impulse);

	UFUNCTION()
		void SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	UStaticMeshComponent* GetMeshComp();

	UFUNCTION()
		void InitMat(int Mat);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
