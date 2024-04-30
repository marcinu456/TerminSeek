#pragma once
#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ETerminalCommands : uint8
{
	TC_Help UMETA(DisplayName = "Help")
};


struct FTerminalCommands
{

	FString GetCommandString(const ETerminalCommands CommandInfo)
	{
		switch(CommandInfo)
		{
		case ETerminalCommands::TC_Help:
				return "Help: Displays all available commands\n"
				"Clear: Clears the terminal\n"
				"Exit: Exits the terminal";
		default:
			return "";
		}
	}
};