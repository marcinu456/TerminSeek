// Made by CookieCore


#include "GameTerminalCartridge.h"

#include "Kismet/GameplayStatics.h"
#include "TerminSeek/Obstacle/ObstacleManager.h"
#include "TerminSeek/Obstacle/ObsticleInfo.h"

void UGameTerminalCartridge::BeginPlay()
{
	Super::BeginPlay();

	SetObstacleManager();
}

void UGameTerminalCartridge::OnInput(const FString& Input)
{
	GameStart(Input);
}

void UGameTerminalCartridge::GameStart(const FString& Input)
{
	TArray<FString> Buffer = SplitLine(Input);
	if (Buffer[0] == "help")
	{
		if(Buffer[1] == "NONE_PARAMETER")
		{
			PrintLine(TerminalCommand.GetCommandInfo(ETerminalCommands::TC_Help));
		}
		else if(Buffer[1] == "camera")
		{
			PrintLine(TerminalCommand.GetCommandInfo(ETerminalCommands::TC_Camera));
		}
		else if (Buffer[1] == "door")
		{
			PrintLine(TerminalCommand.GetCommandInfo(ETerminalCommands::TC_Door));
		}
		else
		{
			PrintLine(TerminalCommand.GetCommandInfo(ETerminalCommands::TC_Help));
		}
	}
	else if (Buffer[0] == "camera")
	{
		if (Buffer[1] == "NONE_PARAMETER")
		{
			PrintLine(TerminalCommand.GetCommandInfo(ETerminalCommands::TC_Camera));
		}
		else
		{
			Buffer = SplitLine(Buffer[1]);

			if(ObstacleManager)
			{
				PrintLine("Received message " + ObstacleManager->SendCommandAndParameterToObstacle(EObstacleType::OT_Camera, Buffer[0], Buffer[1]));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No ObstacleManager found!"));
			}
		}
	}
	else if (Buffer[0] == "door")
	{
		if (Buffer[1] == "NONE_PARAMETER")
		{
			PrintLine(TerminalCommand.GetCommandInfo(ETerminalCommands::TC_Door));
		}
		else
		{
			Buffer = SplitLine(Buffer[1]);

			if (ObstacleManager)
			{
				PrintLine("Received message " + ObstacleManager->SendCommandAndParameterToObstacle(EObstacleType::OT_Door, Buffer[0], Buffer[1]));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No ObstacleManager found!"));
			}
		}
	}
	else
	{
		PrintLine("Unrecognized command: " + Buffer[0]);
	}
}

TArray<FString> UGameTerminalCartridge::SplitLine(const FString& Line)
{
	TArray<FString> Buffer;
	FString Input = Line;
	FString Left, Right;
	if(Input.Split(TEXT(" "), &Left, &Right))
	{
	Buffer.Emplace(Left);
	Buffer.Emplace(Right);
	}
	else
	{
		Buffer.Emplace(Input);
		Buffer.Add("NONE_PARAMETER");

	}
	return Buffer;
}

void UGameTerminalCartridge::SetObstacleManager()
{
	TArray<AActor*> ActorsToFind;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObstacleManager::StaticClass(), ActorsToFind);
	if(ActorsToFind.Num()>0)
	{
		ObstacleManager = Cast<AObstacleManager>(ActorsToFind[0]);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No ObstacleManager found!"));
	}
}
