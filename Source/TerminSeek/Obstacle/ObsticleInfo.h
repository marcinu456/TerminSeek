#pragma once
#include "CoreMinimal.h"
#include "ObsticleInfo.generated.h"

UENUM(BlueprintType)
enum class EObstacleType : uint8
{
	OT_None UMETA(DisplayName = "None"),
	OT_Camera UMETA(DisplayName = "Camera"),
	OT_Door UMETA(DisplayName = "Door")
};