// Made by CookieCore


#include "GameTerminalCartridge.h"

void UGameTerminalCartridge::BeginPlay()
{
	Super::BeginPlay();
}

void UGameTerminalCartridge::OnInput(const FString& Input)
{
	GameStart(Input);
}

void UGameTerminalCartridge::GameStart(const FString& Input)
{
	if (Input == "help")
	{
		PrintLine(TerminalCommand.GetCommandString(ETerminalCommands::TC_Help));
	}
	else
	{
		PrintLine(Input);
	}
}
