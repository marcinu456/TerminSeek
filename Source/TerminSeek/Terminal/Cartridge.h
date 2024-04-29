// Made by CookieCore

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cartridge.generated.h"


UCLASS(Abstract)
class TERMINSEEK_API UCartridge : public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void OnInput(const FString& Input) PURE_VIRTUAL(UCartridge::OnInput, );
protected:
	void BeginPlay() override;

	void PrintLine(const FString& Line) const;
	void PrintLine(const TCHAR* Line) const; // Avoid template for this case.
	template<SIZE_T N, typename ...Types>
	void PrintLine(const TCHAR(&Fmt)[N], Types... Args) const
	{
		PrintLine(FString::Printf(Fmt, Args...));
	}
	void ClearScreen() const;
private:
	UPROPERTY()
	class UTerminal* Terminal;
};