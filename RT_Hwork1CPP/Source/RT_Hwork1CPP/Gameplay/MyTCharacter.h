// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RT_Hwork1CPPCharacter.h"
#include "CoinInHand.h"
#include "Components/ArrowComponent.h"
#include "MyTCharacter.generated.h"


/**
 * 
 */
UCLASS()
class RT_HWORK1CPP_API AMyTCharacter : public ART_Hwork1CPPCharacter
{
	GENERATED_BODY()
public:
	AMyTCharacter();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UArrowComponent* PickArrow;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UArrowComponent* ThrowStartArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int CoinGold;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int CoinSilver;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int CoinTotal;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float ThrowPower;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACoinInHand * MyCoinInHand;

	UFUNCTION(BlueprintCallable)
		void PickCoinInHand(ACoinInHand* Coin);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ThrowCoinInHandAction();
};
