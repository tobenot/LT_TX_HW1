// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "WallBox.generated.h"


UCLASS()
class RT_HWORK1CPP_API AWallBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallBox();

	// 正方体碰撞组件。
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent* CollisionComponent;

	// 静态网格体组件。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int MyMat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool DesFlag;

	UFUNCTION()
		void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
		void DesWallBoxEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
