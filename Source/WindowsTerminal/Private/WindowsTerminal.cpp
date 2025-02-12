#include "WindowsTerminal.h"

DEFINE_LOG_CATEGORY(WindowsTerminal);

#define LOCTEXT_NAMESPACE "FWindowsTerminal"

void FWindowsTerminal::StartupModule()
{
	UE_LOG(WindowsTerminal, Warning, TEXT("WindowsTerminal module has been loaded"));
}

void FWindowsTerminal::ShutdownModule()
{
	UE_LOG(WindowsTerminal, Warning, TEXT("WindowsTerminal module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWindowsTerminal, WindowsTerminal)