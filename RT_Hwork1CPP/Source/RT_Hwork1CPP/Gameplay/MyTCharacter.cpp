// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "../Gameplay/MyTCharacter.h"

AMyTCharacter::AMyTCharacter(){

	PickArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("PickArrow"));
	PickArrow->SetupAttachment(GetMesh(), FName(TEXT("hand_r")));

	ThrowStartArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ThrowStartArrow"));
	ThrowStartArrow->SetupAttachment(RootComponent);

	ThrowPower = 1500;
}

void AMyTCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ThrowCoin", IE_Pressed, this, &AMyTCharacter::ThrowCoinInHandAction);

}




void AMyTCharacter::PickCoinInHand(ACoinInHand* Coin) {
	if (Coin) {
		MyCoinInHand = Coin;
		MyCoinInHand->GetMeshComp()->AttachToComponent(PickArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));

	}

}

void AMyTCharacter::ThrowCoinInHandAction() {
	
	if (MyCoinInHand) {
		MyCoinInHand->GetMeshComp()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		MyCoinInHand->GetMeshComp()->SetWorldLocation(ThrowStartArrow->GetComponentLocation());
		MyCoinInHand->ThrowCoin((GetFollowCamera()->GetForwardVector())* ThrowPower);
		MyCoinInHand = nullptr;
	}

}