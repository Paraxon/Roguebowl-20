module;
#include <Windows.h>
#include <DbgHelp.h>
export module CallStack;

export class CallStack
{
public:
	CallStack();
	~CallStack();

private:

};

CallStack::CallStack()
{
    DWORD  error;
    HANDLE hProcess = GetCurrentProcess();;

    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);

    if (!SymInitialize(hProcess, nullptr, true))
        return;

    CONTEXT context;
    RtlCaptureContext(&context);

    STACKFRAME frame = {};
    frame.AddrPC = context.Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context.Esp;
    frame.AddrStack.Mode = AddrModeFlat;
}

CallStack::~CallStack()
{
}