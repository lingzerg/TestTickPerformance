// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TestCppCollectTickActor.h"
#include "TickPerformanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TESTTICKPERFORMANCE_API UTickPerformanceSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "TickPerformance")
	void SpawnActor(int count,TSubclassOf<AActor> BlueprintClass);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickPerformance")
	bool isTestOptimization = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickPerformance")
	TArray<ATestCppCollectTickActor*> tickActorList;

	
	virtual TStatId GetStatId() const override;
	// Tick 是否启用
	virtual bool IsTickable() const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
