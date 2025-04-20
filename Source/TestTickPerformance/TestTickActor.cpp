#include "TestTickActor.h"

ATestTickActor::ATestTickActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestTickActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestTickActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	RandomLocation(DeltaTime);
}

void ATestTickActor::RandomLocation(float DeltaTime)
{
	// 设置随机坐标（假设范围在 [-5000,5000]）
	FVector RandomLocation = FVector(
		FMath::RandRange(-5000, 5000),
		FMath::RandRange(-5000, 5000),
		FMath::RandRange(0, 1000)
	);
	this->SetActorLocation(RandomLocation);
	
}