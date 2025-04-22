// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestCppCollectTickActor.generated.h"

UCLASS()
class TESTTICKPERFORMANCE_API ATestCppCollectTickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCppCollectTickActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//void RandomLocation(float DeltaTime);
	
};
