// Made by CookieCore

#pragma once

#include "CoreMinimal.h"
#include "ObstacleInterface.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UCLASS()
class TERMINSEEK_API AObstacleBase : public AActor, public IObstacleInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Obstacle")
	EObstacleType ObstacleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Obstacle")
	FString ObstacleName;

//Interface Functions
public:
	virtual EObstacleType GetObstacleType_Implementation() override { return ObstacleType; }

	virtual FString GetObstacleName_Implementation() override { return ObstacleName; }

	virtual FString ReceiveCommandAndParameter_Implementation(const FString& Parameter) override { return "false"; }
};
