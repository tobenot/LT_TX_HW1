// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTCharacter.h"
#include "CoinInHand.h"
#include "CoinPickup.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Gameplay/TurretBullet.h"

// Sets default values
ATurretBullet::ATurretBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		// 用球体进行简单的碰撞展示。
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// 设置球体的碰撞半径。
		CollisionComponent->InitSphereRadius(50.0f);
		// 设置球体的碰撞规则。
		CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		// 将根组件设置为碰撞组件。
		RootComponent = CollisionComponent;
	}

	CoinCheckComp = CreateDefaultSubobject<USphereComponent>(TEXT("CoinCheckComp"));
	CoinCheckComp->InitSphereRadius(300.0f);
	CoinCheckComp->SetupAttachment(RootComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);


	if (!ProjectileMovementComponent)
	{
		// 使用此组件驱动发射物的移动。
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 5000.0f;
		ProjectileMovementComponent->MaxSpeed = 5000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	// 3 秒后删除发射物。
	InitialLifeSpan = 3.0f;

	// 组件击中某物时调用的事件。
	CollisionComponent->OnComponentHit.AddDynamic(this, &ATurretBullet::OnHit);

	CoinCheckComp->OnComponentBeginOverlap.AddDynamic(this, &ATurretBullet::CheckSphereBeginOverlap);
}
void ATurretBullet::InitMat(int Mat)
{
	MyMat = Mat;
}

// Called when the game starts or when spawned
void ATurretBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATurretBullet::GoBack() {
	//被弹一下

	ProjectileMovementComponent->MaxSpeed = 0.8 * ProjectileMovementComponent->MaxSpeed;

	FRotator MyFaceRot = UKismetMathLibrary::FindLookAtRotation(FVector(0), ProjectileMovementComponent->Velocity);

	ProjectileMovementComponent->Velocity =
		ProjectileMovementComponent->MaxSpeed *
		((0.4 * UKismetMathLibrary::GetUpVector(MyFaceRot)) + (0.6 * UKismetMathLibrary::GetRightVector(MyFaceRot)));

		//((0.2 * ProjectileMovementComponent->Velocity.UpVector) + (0.8 * ProjectileMovementComponent->Velocity));
		//这样使用获得的好像是上分量、右分量? 效果：只会往上走，不会往右
}



// 初始化射击方向上发射物速度的函数。
void ATurretBullet::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// 当发射物击中物体时会调用的函数。
void ATurretBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 10.0f, Hit.ImpactPoint);
	}

	if (OtherActor)
	{
		AMyTCharacter* HitPawn = Cast<AMyTCharacter>(OtherActor);
		if (HitPawn)
		{
			FVector LaunchVector = GetActorForwardVector() * 0.6f * (ProjectileMovementComponent->MaxSpeed);
			LaunchVector.Z = 0;
			HitPawn->LaunchCharacter(LaunchVector, 1, 1);
		}
	}

	//Destroy();
}

void ATurretBullet::CheckSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ACoinInHand* Other = Cast<ACoinInHand>(OtherActor);
		if (Other)
		{
			if (Other->MyMat == MyMat)
			{
				GoBack();
			}
		}
		else
		{
			ACoinPickup* Other2 = Cast<ACoinPickup>(OtherActor);
			if (Other2)
			{
				if (Other2->MyMat == MyMat)
				{
					GoBack();
				}
			}
		}
	}
}