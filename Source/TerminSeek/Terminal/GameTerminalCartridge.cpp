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
	TArray<FString> Buffer = SplitLine(Input);
	if (Buffer[0] == "help")
	{
		PrintLine(TerminalCommand.GetCommandString(ETerminalCommands::TC_Help));
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
	}
	return Buffer;
}
