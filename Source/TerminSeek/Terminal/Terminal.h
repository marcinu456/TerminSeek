// Made by CookieCore

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Terminal.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTextUpdateSignature, FString, Text);

struct FKey;

struct FTerminalHistory
{

	TArray<FString> Lines;
	int32 CurrentIndex = 0;
	FString CurrentLine;

	void Add(const FString& Line)
	{
		Lines.Add(Line);
		CurrentIndex = Lines.Num();
	}

	void SetIndexToLast()
	{
		CurrentIndex = Lines.Num();
	}

	FString GetPrevious()
	{
		if (CurrentIndex > 0)
		{
			CurrentIndex--;
		}
		return CurrentIndex < Lines.Num() ? Lines[CurrentIndex] : FString();
	}

	FString GetNext()
	{
		if (CurrentIndex < Lines.Num())
		{
			CurrentIndex++;
		}
		return CurrentIndex < Lines.Num() ? Lines[CurrentIndex] : CurrentLine;
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TERMINSEEK_API UTerminal : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Terminal")
	FTextUpdateSignature TextUpdated;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetScreenText() const;

	UFUNCTION(BlueprintCallable)
	void ActivateTerminal();

	UFUNCTION(BlueprintCallable)
	void DeactivateTerminal() const;

	void PrintLine(const FString& Line);
	void ClearScreen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void OnKeyDown(FKey Key);
	TArray<FString> WrapLines(const TArray<FString>& Lines) const;
	void Truncate(TArray<FString>& Lines) const;
	FString JoinWithNewline(const TArray<FString>& Lines) const;
	void AcceptInputLine();
	void Backspace();
	void UpKey();
	void DownKey();
	FString GetKeyString(FKey Key) const;
	void UpdateText();


	UPROPERTY(EditAnywhere)
	int32 MaxLines = 10;

	UPROPERTY(EditAnywhere)
	int32 MaxColumns = 70;

	TArray<FString> Buffer;
	FString InputLine;

	int32 PressedBindingIndex;
	int32 RepeatBindingIndex;

	FTerminalHistory TerminalHistory;
};
