#pragma once
#include "CoreMinimal.h"
#include "TerminalCommands.generated.h"


UENUM(BlueprintType)
enum class ETerminalCommands : uint8
{
	TC_Help UMETA(DisplayName = "Help"),
	TC_Camera UMETA(DisplayName = "Camera"),
	TC_Door UMETA(DisplayName = "Door")
};


struct FTerminalCommands
{

	FString GetCommandInfo(const ETerminalCommands CommandInfo)
	{
		switch(CommandInfo)
		{
		case ETerminalCommands::TC_Help:
				return "Help: Displays all available commands\n"
				"help [parameter] show help about command below\n"
				"camera: Get camera\n"
				"door: Get door";
		case ETerminalCommands::TC_Camera:
			return "camera [parameter] [camera_name]\n "
				"Parameters of camera command:\n"
				"off - turn of camera\n"
				"on - turn of camera";
		case ETerminalCommands::TC_Door:
			return "door [parameter] [door_name]\n "
				"Parameters of door command:\n"
				"open - open door\n"
				"close - close door";
		default:
			return "";
		}
	}
};