// Made by CookieCore

#pragma once

#include "CoreMinimal.h"
#include "Base/Cartridge.h"
#include "TerminalCommands.h"
#include "GameTerminalCartridge.generated.h"

class AObstacleManager;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TERMINSEEK_API UGameTerminalCartridge : public UCartridge
{
	GENERATED_BODY()

protected:
		virtual void BeginPlay() override;

public:
		virtual void OnInput(const FString& Input) override;

private:
	void GameStart(const FString& Input);

	FTerminalCommands TerminalCommand;

	TArray<FString> SplitLine(const FString& Line);

	UPROPERTY()
	AObstacleManager *ObstacleManager;

	void SetObstacleManager();

};
