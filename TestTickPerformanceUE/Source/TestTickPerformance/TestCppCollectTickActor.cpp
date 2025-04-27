// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCppCollectTickActor.h"

#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ATestCppCollectTickActor::ATestCppCollectTickActor()
{

}

// Called when the game starts or when spawned
void ATestCppCollectTickActor::BeginPlay()
{
	Super::BeginPlay();
	//
	// TArray<UInstancedStaticMeshComponent*> Components;
	// GetComponents<UInstancedStaticMeshComponent>(Components);
 //    
	// if (Components.Num() > 0) {
	// 	ISMComponent = Components[0];
	// }
	
	SetReplicates(false);
	SetReplicateMovement(false);
	SetActorEnableCollision(false);

	SetActorEnableCollision(false);
}

void ATestCppCollectTickActor::RandomLocation(float DeltaTime)
{
	// 设置随机坐标（假设范围在 [-5000,5000]）
	FVector RandomLocation = FVector(
		FMath::RandRange(-5000, 5000),
		FMath::RandRange(-5000, 5000),
		FMath::RandRange(0, 1000)
	);
	
	this->SetActorLocation(RandomLocation);
}
// 	