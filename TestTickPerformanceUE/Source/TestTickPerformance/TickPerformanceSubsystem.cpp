// Fill out your copyright notice in the Description page of Project Settings.


#include "TickPerformanceSubsystem.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"

TArray<FVector> Locations;


void UTickPerformanceSubsystem::Tick(float DeltaTime)
{
	const int32 CurrentCount = tickActorList.Num();
	
	if (CurrentCount != 0)
	{
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
					FMath::RandRange(0, 50000),
					FMath::RandRange(0, 50000),
					FMath::RandRange(0, 50000)
					);
			
				tickActorList[i]->SetActorLocation(RandomLocation,false,nullptr,  ETeleportType::None);
			}
		}
	}
	
	if (ManagedISMs.Num() == 0)
	{
		return;
	}
	for (auto ISM : ManagedISMs)
	{
		TArray<FTransform> InstanceTransforms;
		const int32 InstanceCount = ISM->GetInstanceCount();
		
		for (int32 InstanceIndex = 0; InstanceIndex < InstanceCount; ++InstanceIndex) {
			FTransform InstanceTransform;
			bool bSuccess = ISM->GetInstanceTransform(InstanceIndex, InstanceTransform, true); // 第三个参数表示是否返回世界坐标
			if (bSuccess) {
				FVector RandomLocation = FVector(
							FMath::RandRange(0, 50000),
							FMath::RandRange(0, 50000),
							FMath::RandRange(0, 50000)
							);
				InstanceTransform.SetLocation(RandomLocation);
				InstanceTransforms.Add(InstanceTransform);
			}
		}
		ISM->SetCustomDataValue(0, 0	, 0);
		// 批量提交更新
		ISM->BatchUpdateInstancesTransforms(
			0,
			InstanceTransforms, 
			true,  // 更新世界坐标
			true   // 立即刷新渲染状态
		);
	}
}

int UTickPerformanceSubsystem::getInstanceCount() {
	if (ManagedISMs.Num() == 0)
	{
		return 0;	
	}
	int32 instanceCount = 0;
	for (auto ISM : ManagedISMs)
	{
		instanceCount += ISM->GetInstanceCount();
	}
	return instanceCount;
	
}



void UTickPerformanceSubsystem::SpawnActor(int count, TSubclassOf<AActor> BlueprintClass)
{
	if (BlueprintClass)
	{
		//使用当前毫秒数作为spawn的唯一标记
		int32 Milliseconds = FPlatformTime::Seconds();
		
		int len = tickActorList.Num();
		for (int i = 0; i < count; i++)
		{
			//FString NameStr = FGuid::NewGuid().ToString(); // 生成唯一GUID字符串
			
			FActorSpawnParameters SpawnParams;
			FString sname = FString::Printf(TEXT("CollectTick_%d_%d_cpp"), len+i, Milliseconds);
			SpawnParams.Name = FName(*sname); // 创建一个唯一的名称
			//SpawnParams.Name = FName(NameStr);// FName(*NameStr);
			ATestCppCollectTickActor* spawn = GetWorld()->SpawnActor<ATestCppCollectTickActor>(
				BlueprintClass,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
			
#if WITH_EDITOR
			spawn->SetActorLabel(sname);
#endif
			tickActorList.Add(spawn);
			
		}
		
	}
}

void UTickPerformanceSubsystem::SpawnInstance(int count,TSubclassOf<AActor> BlueprintClass)
{
	
	if (BlueprintClass)
	{
		int len = tickInstanceActorList.Num();
		UInstancedStaticMeshComponent *ISM;
		int32 intanceCount = 0;
		if (len > 0)
		{
			ISM = tickInstanceActorList[len - 1]->FindComponentByClass<UInstancedStaticMeshComponent>();
			if (!ISM)
			{
				return;
			}
			intanceCount = ISM->GetInstanceCount();
			if (intanceCount < 20000) //每个actor的实例不要超过20000 如果大于20000 , 则spawn 一个新的actor
			{
				// 初始化一些默认实例
				FTransform InitialTransform(FVector(0, 0, 0));
				for (int i = 0; i < count; i++)
				{
					ISM->AddInstance(InitialTransform);
				}
			}
		}
		int32 Milliseconds = FPlatformTime::Seconds();
		
		if (len == 0 || intanceCount >= 20000)
		{
			FActorSpawnParameters SpawnParams;
			FString sname = FString::Printf(TEXT("CollectTick_%d_%d_ins"), len, Milliseconds);
			SpawnParams.Name = FName(*sname); // 创建一个唯一的名称
			ATestCppCollectTickActor* spawn = GetWorld()->SpawnActor<ATestCppCollectTickActor>(
			 BlueprintClass,
			 FVector::ZeroVector,
			 FRotator::ZeroRotator,
			 SpawnParams
			 );
			UInstancedStaticMeshComponent* newISM = spawn->FindComponentByClass<UInstancedStaticMeshComponent>();
			if (newISM && !ManagedISMs.Contains(newISM))
			{
				ManagedISMs.Add(newISM);
			}
			FTransform InitialTransform(FVector(0, 0, 0));
			for (int i = 0; i < count; i++)
			{
				newISM->AddInstance(InitialTransform);
			}
#if WITH_EDITOR
			spawn->SetActorLabel(sname);
#endif
			tickInstanceActorList.Add(spawn);
			return;
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

void UTickPerformanceSubsystem::Clear()
{
	ManagedISMs.Empty();
	tickActorList.Empty();
	tickInstanceActorList.Empty();
}
