module;
#include <Windows.h> //Must be defined before DbgHelp
#include <DbgHelp.h>
export module WinTrace;

import StackTrace;

//https://docs.microsoft.com/en-us/windows/win32/debug/symbol-handling
export class SymbolHandler
{
public:
	SymbolHandler(DWORD options, HANDLE process = GetCurrentProcess());
	~SymbolHandler();
	//Rule of 5
	SymbolHandler(const SymbolHandler&) = delete;
	SymbolHandler(SymbolHandler&&) = delete;
	SymbolHandler& operator=(const SymbolHandler&) = delete;
	SymbolHandler& operator=(SymbolHandler&&) = delete;
private:
	HANDLE _process;
};

export class WinTrace : public StackTrace
{
public:
	[[nodiscard]] WinTrace();
	[[nodiscard]] WinTrace(CONTEXT context);
private:
	void initalize(CONTEXT context);
};