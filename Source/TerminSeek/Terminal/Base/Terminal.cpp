// Made by CookieCore


#include "Terminal.h"
#include "Cartridge.h"

constexpr TCHAR GPrompt[4] = TEXT("$> ");

// Called when the game starts
void UTerminal::BeginPlay()
{
	Super::BeginPlay();
	UpdateCurrentTextLine();
}

void UTerminal::ActivateTerminal()
{
	FInputKeyBinding PressedBinding(EKeys::AnyKey, EInputEvent::IE_Pressed);
	PressedBinding.KeyDelegate.BindDelegate(this, &UTerminal::OnKeyDown);

	FInputKeyBinding RepeatBinding(EKeys::AnyKey, EInputEvent::IE_Repeat);
	RepeatBinding.KeyDelegate.BindDelegate(this, &UTerminal::OnKeyDown);

	if (GetOwner()->InputComponent == nullptr) return;

	PressedBindingIndex = GetOwner()->InputComponent->KeyBindings.Emplace(MoveTemp(PressedBinding));
	RepeatBindingIndex = GetOwner()->InputComponent->KeyBindings.Emplace(MoveTemp(RepeatBinding));
}

void UTerminal::DeactivateTerminal() const
{
	if (GetOwner()->InputComponent == nullptr) return;

	// Must do in this order as RepeatBindingIndex > PressedBindingIndex so would change when first is removed
	GetOwner()->InputComponent->KeyBindings.RemoveAt(RepeatBindingIndex);
	GetOwner()->InputComponent->KeyBindings.RemoveAt(PressedBindingIndex);
}

void UTerminal::PrintLine(const FString& Line)
{
	TArray<FString> Buffer;
	FString Input = Line;
	FString Left, Right;
	while (Input.Split(TEXT("\n"), &Left, &Right))
	{
		Buffer.Emplace(Left);
		Input = Right;
	}
	Buffer.Emplace(Input);
	auto buffLine = Line;
	WriteLine(buffLine);
}

void UTerminal::ClearScreen()
{
	InputLine = TEXT("");
	UpdateCurrentTextLine();
}

FString UTerminal::GetScreenText() const
{
	TArray<FString> FullTerminal;
	FullTerminal.Add(GPrompt + InputLine);

	// WrapLines
	TArray<FString> WrappedLines(WrapLines(FullTerminal));
	Truncate(WrappedLines);

	return JoinWithNewline(WrappedLines);
}

TArray<FString> UTerminal::WrapLines(const TArray<FString>& Lines) const
{
	TArray<FString> WrappedLines;
	for (auto&& Line : Lines)
	{
		FString CurrentLine = Line;
		do
		{
			WrappedLines.Add(CurrentLine.Left(MaxColumns));
			CurrentLine = CurrentLine.RightChop(MaxColumns);
		} while (CurrentLine.Len() > 0);
	}
	return WrappedLines;
}

void UTerminal::Truncate(TArray<FString>& Lines) const
{
	while (Lines.Num() > MaxLines)
	{
		Lines.RemoveAt(0);
	}
}

FString UTerminal::JoinWithNewline(const TArray<FString>& Lines) const
{
	FString Result;
	for (auto&& Line : Lines)
	{
		Result += Line + TEXT(" <br>");
	}
	return Result;
}

void UTerminal::OnKeyDown(FKey Key)
{
	if (Key == EKeys::Enter)
	{
		AcceptInputLine();
	}
	else if (Key == EKeys::BackSpace)
	{
		Backspace();
	}
	else if (Key == EKeys::Up)
	{
		UpKey();
	}
	else if (Key == EKeys::Down)
	{
		DownKey();
	}
	else 
	{
		const FString KeyString = GetKeyString(Key);
		const FModifierKeysState KeyState = FSlateApplication::Get().GetModifierKeys();
		if (KeyState.IsShiftDown() || KeyState.AreCapsLocked())
		{
			InputLine += KeyString.ToUpper();
		}
		else
		{
			InputLine += KeyString.ToLower();
		}
		TerminalHistory.CurrentLine = InputLine;
		TerminalHistory.SetIndexToLast();
	}
	UpdateCurrentTextLine();

}


void UTerminal::AcceptInputLine()
{
	//Buffer.Emplace(GPrompt + InputLine);
	auto Cartridge = GetOwner()->FindComponentByClass<UCartridge>();
	if (Cartridge != nullptr)
	{
		Cartridge->OnInput(InputLine);
	}
	TerminalHistory.Add(InputLine);
	InputLine = TEXT("");

}

void UTerminal::Backspace()
{
	if (InputLine.Len() > 0)
	{
		InputLine.RemoveAt(InputLine.Len() - 1);
	}
}

void UTerminal::UpKey()
{
	InputLine = TerminalHistory.GetPrevious();
}

void UTerminal::DownKey()
{
	InputLine = TerminalHistory.GetNext();
}

FString UTerminal::GetKeyString(FKey Key) const
{
	const uint32* KeyCode = nullptr;
	const uint32* CharCode = nullptr;
	FInputKeyManager::Get().GetCodesFromKey(Key, KeyCode, CharCode);
	if (CharCode != nullptr)
	{
		ANSICHAR Char[2] = { static_cast<ANSICHAR>(*CharCode), '\0' };
		return ANSI_TO_TCHAR(Char);
	}

	return TEXT("");
}

void UTerminal::UpdateCurrentTextLine()
{
	TextUpdated.Broadcast(InputLine);
}

void UTerminal::WriteLine(FString& Line)
{
	TextWriteLine.Broadcast(Line);
}
