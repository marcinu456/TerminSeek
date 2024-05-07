// Made by CookieCore

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleManager.generated.h"

enum class EObstacleType : uint8;
class AObstacleBase;

UCLASS()
class TERMINSEEK_API AObstacleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString SendCommandAndParameterToObstacle(EObstacleType ObstacleType, FString Parameter, FString ObstacleName);

private:
	TArray<AObstacleBase* > Obstacles;
};
