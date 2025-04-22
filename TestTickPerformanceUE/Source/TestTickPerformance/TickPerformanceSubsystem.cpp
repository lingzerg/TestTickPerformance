// Fill out your copyright notice in the Description page of Project Settings.


#include "TickPerformanceSubsystem.h"

TArray<FVector> Locations;


void UTickPerformanceSubsystem::Tick(float DeltaTime)
{
	const int32 CurrentCount = tickActorList.Num();
	
	if (CurrentCount == 0)
	{
		return;
	}
	
	if (isTestOptimization)
	{
		for (int32 i = 0; i < CurrentCount; i++)
		{
			tickActorList[i]->SetActorLocation(Locations[FMath::RandRange(0, 100000)],false);
		}
	} else
	{
		for (int32 i = 0; i < CurrentCount; i ++)
		{
			FVector RandomLocation = FVector(
				FMath::RandRange(0, 5000),
				FMath::RandRange(0, 5000),
				FMath::RandRange(0, 5000)
				);
			tickActorList[i]->SetActorLocation(RandomLocation,false);
		}
	}

	
}

void UTickPerformanceSubsystem::SpawnActor(int count, TSubclassOf<AActor> BlueprintClass)
{
	if (BlueprintClass)
	{
		for (int i = 0; i < count; i++)
		{
			FString NameStr = FGuid::NewGuid().ToString(); // 生成唯一GUID字符串
			
			FActorSpawnParameters SpawnParams;
			//FString NameStr = FString::Printf(TEXT("CollectTick_%d"),i); // 名称从当前池大小递增
			SpawnParams.Name = FName(*NameStr);
			ATestCppCollectTickActor* spawn = GetWorld()->SpawnActor<ATestCppCollectTickActor>(
			 BlueprintClass,
			 FVector::ZeroVector,
			 FRotator::ZeroRotator,
			 SpawnParams
		 );
			tickActorList.Add(spawn);
		}
	}
}


void UTickPerformanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Locations.SetNum(110000);
	for(int i =0; i < 110000; i++)
	{
		Locations[i] = FVector(
			FMath::FRand() * 10000.f - 5000.f,
		FMath::FRand() * 10000.f - 5000.f,
		FMath::FRand() * 1000.f
		);
	}
}

bool UTickPerformanceSubsystem::IsTickable() const
{
	return true;
}

TStatId UTickPerformanceSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMyCustomSubsystem, STATGROUP_Tickables);
}


