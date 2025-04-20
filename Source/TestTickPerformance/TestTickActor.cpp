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
	
	FVector RandomLocation = FVector(
		FMath::RandRange(-5000, 5000),
		FMath::RandRange(-5000, 5000),
		FMath::RandRange(0, 1000)
	);
	this->SetActorLocation(RandomLocation);
}