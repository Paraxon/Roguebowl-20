import WinTrace;
import StackTrace;
#include <Windows.h> //Must be defined before DbgHelp
#include <DbgHelp.h>
#include <cstddef>
#include <vector>
#include <string>

SymbolHandler::SymbolHandler(DWORD options, HANDLE process) : _process(process)
{
	SymInitialize(_process, nullptr, true);
	SymSetOptions(options);
}

SymbolHandler::~SymbolHandler()
{
	SymCleanup(_process);
}

WinTrace::WinTrace()
{
	CONTEXT context;
	RtlCaptureContext(&context);
	initalize(context);
}

WinTrace::WinTrace(CONTEXT context)
{
	initalize(context);
}

void WinTrace::initalize(CONTEXT context)
{
	const auto process = GetCurrentProcess();
	const SymbolHandler symbols{ SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES, process };

	constexpr DWORD machine
	{
		#ifdef _M_X64 
				IMAGE_FILE_MACHINE_AMD64
		#elif _M_IX86 
				IMAGE_FILE_MACHINE_I386
		#elif _M_IA64 
				IMAGE_FILE_MACHINE_IA64
		#endif
	};

	//https://docs.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-stackwalk
	const auto walk = [machine, process, thread = GetCurrentThread()](STACKFRAME& frame, CONTEXT& context) {
		return StackWalk(
			machine,				//Machine Type
			process,				//Process handle
			thread,					//Thread handle, optional with valid ReadMemoryRoutine
			&frame,					//Stackframe Out
			&context,				//Context
			nullptr,				//ReadMemoryRoutine, if null uses default
			&SymFunctionTableAccess,//FunctionTableAccessRoutine
			&SymGetModuleBase,		//GetModuleBaseRoutine
			nullptr);				//TranslateAddress
	};

	for (STACKFRAME frame{}; walk(frame, context);)
	{
		constexpr auto name_length = 256;
		union {
			SYMBOL_INFO value;
			std::byte buffer[sizeof(SYMBOL_INFO) + name_length];
		} symbol;

		symbol.value = {
			.SizeOfStruct = sizeof(SYMBOL_INFO),
			.MaxNameLen = name_length + 1
		};

		IMAGEHLP_LINE line{ .SizeOfStruct = sizeof(IMAGEHLP_LINE) };
		DWORD displacment;

		SymFromAddr(process, frame.AddrPC.Offset, 0, &symbol.value);
		if (SymGetLineFromAddr(process, frame.AddrPC.Offset, &displacment, &line))
			frames().emplace_back(symbol.value.Name, line.FileName, line.LineNumber);
		else
			frames().emplace_back(symbol.value.Name);
	}
}