import WinTrace;
#include <iostream>
#include <fmt/core.h>
#include <Windows.h>


int main()
try
{
	CONTEXT context;
	RtlCaptureContext(&context);
	throw std::make_unique<WinTrace>(context);
}
catch (const std::unique_ptr<WinTrace> & trace)
{
	for (auto i = 0; const auto frame : *trace)
	{
		if (frame.source)
			std::cout << fmt::format("{}: {} ({}: {})\n", i++, frame.name, frame.source->filename().string(), *frame.line);
		else
			std::cout << fmt::format("{}: {}\n", i++, frame.name);
	}
}