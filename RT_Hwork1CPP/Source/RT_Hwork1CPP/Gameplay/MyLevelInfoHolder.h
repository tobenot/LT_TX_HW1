// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "MyLevelInfoHolder.generated.h"

UCLASS()
class RT_HWORK1CPP_API AMyLevelInfoHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyLevelInfoHolder();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* TextComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CoinGoal_Total;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CoinGoal_Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CoinGoal_Silver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelHeader;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
