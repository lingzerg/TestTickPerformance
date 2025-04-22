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
		FMath::RandRange(0, 50000),
		FMath::RandRange(0, 50000),
		FMath::RandRange(0, 50000)
	);
	this->SetActorLocation(RandomLocation,false,nullptr, 
		ETeleportType::None);
}