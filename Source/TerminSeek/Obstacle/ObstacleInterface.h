// Made by CookieCore

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObsticleInfo.h"
#include "ObstacleInterface.generated.h"

/**
 * 
 */

UINTERFACE(MinimalAPI, Blueprintable)
class UObstacleInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IObstacleInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Obstacle")
	EObstacleType GetObstacleType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Obstacle")
	FString GetObstacleName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Obstacle")
	FString ReceiveCommandAndParameter(const FString& Parameter);


};