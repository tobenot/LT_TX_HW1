// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TurretBullet.generated.h"

UCLASS()
class RT_HWORK1CPP_API ATurretBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretBullet();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MyMat;

	// ������ײ�����
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// ��̬�����������
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		UStaticMeshComponent* MeshComp;
	// ���������������
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CoinCheckComp;

	// �������ƶ������
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// ��ʼ����������Ϸ������ٶȵĺ�����
	void FireInDirection(const FVector& ShootDirection);

	// ���������������ʱ����õĺ�����
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void CheckSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void GoBack();
	UFUNCTION()
	void InitMat(int Mat);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
