// Made by CookieCore


#include "ObstacleManager.h"
#include "EngineUtils.h"
#include "ObstacleBase.h"

// Sets default values
AObstacleManager::AObstacleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleManager::BeginPlay()
{
	Super::BeginPlay();

	//Get all the obstacles in the level
	for(TActorIterator<AObstacleBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Obstacles.Add(*ActorItr);
	}

}

// Called every frame
void AObstacleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

