#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestTickActor.generated.h"

UCLASS()
class TESTTICKPERFORMANCE_API ATestTickActor : public AActor
{
	GENERATED_BODY()
public :
	ATestTickActor();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};