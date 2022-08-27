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

	// 球体碰撞组件。
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// 静态网格体组件。
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		UStaticMeshComponent* MeshComp;
	// 反弹球体检测组件。
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CoinCheckComp;

	// 发射物移动组件。
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// 初始化射击方向上发射物速度的函数。
	void FireInDirection(const FVector& ShootDirection);

	// 当发射物击中物体时会调用的函数。
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
