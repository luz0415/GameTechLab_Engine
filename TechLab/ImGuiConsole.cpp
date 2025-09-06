#include "ImGuiConsole.h"

UImGuiConsole::UImGuiConsole()
{
	AppConsole = make_unique<ImGuiAppConsole>();
}

UImGuiConsole::~UImGuiConsole()
{
}

void UImGuiConsole::Render()
{
	if (AppConsole)
	{
		AppConsole->Draw("Console", nullptr);
	}
}

void UImGuiConsole::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	if (AppConsole)
	{
		va_list args;
		va_start(args, fmt);
		AddLog(fmt, args);   // AddLog(...)와 동일한 효과
		va_end(args);
	}
}