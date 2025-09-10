#include "ImGuiConsole.h"

UImGuiConsole::UImGuiConsole()
{
	AppConsole = new ImGuiAppConsole();
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

void UImGuiConsole::AddLogV(const char* fmt, va_list args)
{
	if (AppConsole)
	{
		char buf[1024];
		vsnprintf(buf, sizeof(buf), fmt, args);
		AppConsole->AddLog("%s", buf);
	}
}

void UImGuiConsole::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	if (AppConsole)
	{
		char buf[1024];

		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);

		AppConsole->AddLog("%s", buf);   // AddLog(...)와 동일한 효과
	}
}