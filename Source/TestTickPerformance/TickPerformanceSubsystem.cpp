// Fill out your copyright notice in the Description page of Project Settings.


#include "TickPerformanceSubsystem.h"


void UTickPerformanceSubsystem::Tick(float DeltaTime)
{
	const int32 CurrentCount = tickActorList.Num();
	
	const int32 ChunkSize = 64; 
	if (CurrentCount == 0)
	{
		return;
	}
	
	if (isTestOptimization)
	{
		for (int32 i = 0; i < CurrentCount; i += ChunkSize)
		{
			const int32 EndIndex = FMath::Min(i + ChunkSize, CurrentCount);
			for (int32 j = i; j < EndIndex; ++j)
			{
				FVector RandomLocation = FVector(
				FMath::RandRange(-5000, 5000),
				FMath::RandRange(-5000, 5000),
				FMath::RandRange(0, 1000)
			);
				tickActorList[j]->SetActorLocation(RandomLocation);
			}
		}
	} else
	{
		for (int32 i = 0; i < CurrentCount; i += ChunkSize)
		{
			const int32 EndIndex = FMath::Min(i + ChunkSize, CurrentCount);
			for (int32 j = i; j < EndIndex; ++j)
			{
				FVector RandomLocation = FVector(
				FMath::RandRange(-5000, 5000),
				FMath::RandRange(-5000, 5000),
				FMath::RandRange(0, 1000)
			);
				tickActorList[j]->SetActorLocation(RandomLocation);
			}
		}
	}

	
}

void UTickPerformanceSubsystem::SpawnActor(int count, TSubclassOf<AActor> BlueprintClass)
{
	
	if (BlueprintClass)
	{
		for (int i = 0; i < count; i++)
		{
			FActorSpawnParameters SpawnParams;
			FString NameStr = FString::Printf(TEXT("CollectTick_%d"), i); // 名称从当前池大小递增
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
 	
}

bool UTickPerformanceSubsystem::IsTickable() const
{
	return true;
}

TStatId UTickPerformanceSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMyCustomSubsystem, STATGROUP_Tickables);
}


