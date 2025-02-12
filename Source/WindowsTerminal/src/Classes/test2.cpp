
// BEGIN Unreal Terminal
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0A00 // Windows 10
// END Unreal Terminal
#include "test.h"
#include "HAL/PlatformProcess.h"

#include "Windows/WindowsPlatformProcess.h"

#include "Containers/Set.h"
#include "Containers/StringConv.h"
#include "Containers/UnrealString.h"
#include "CoreGlobals.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformAffinity.h"
#include "HAL/PlatformMisc.h"
#include "HAL/FileManager.h"
#include "HAL/UnrealMemory.h"
#include "Internationalization/Internationalization.h"
#include "Logging/LogMacros.h"
#include "Misc/AssertionMacros.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/CoreDelegates.h"
#include "Misc/CoreStats.h"
#include "Misc/Fork.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "Misc/SingleThreadEvent.h"
#include "Misc/PathViews.h"
#include "Misc/TrackedActivity.h"
#include "ProfilingDebugging/CpuProfilerTrace.h"
#include "ProfilingDebugging/CsvProfiler.h"
#include "Stats/Stats.h"
#include "Templates/UnrealTemplate.h"
#include "Trace/Trace.h"
#include "Trace/Trace.inl"

#include "Windows/AllowWindowsPlatformTypes.h"
	#include <shellapi.h>
	#include <ShlObj.h>
	#include <LM.h>
	#include <Psapi.h>
	#include <TlHelp32.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "Windows/WindowsPlatformMisc.h"

// HPCON SetUpPseudoConsole(COORD size)
// {
// 	HRESULT hr = S_OK;
//
// 	// Create communication channels
//
// 	// - Close these after CreateProcess of child application with pseudoconsole object.
// 	HANDLE inputReadSide, outputWriteSide;
//
// 	// - Hold onto these and use them for communication with the child through the pseudoconsole.
// 	HANDLE outputReadSide, inputWriteSide;
//
// 	if (!CreatePipe(&inputReadSide, &inputWriteSide, NULL, 0))
// 	{
// 		// return HRESULT_FROM_WIN32(GetLastError());
// 	}
//
// 	if (!CreatePipe(&outputReadSide, &outputWriteSide, NULL, 0))
// 	{
// 		// return HRESULT_FROM_WIN32(GetLastError());
// 	}
//
// 	HPCON hPC;
// 	hr = CreatePseudoConsole(size, inputReadSide, outputWriteSide, 0, &hPC);
// 	if (FAILED(hr))
// 	{
// 		return hr;
// 	}
//
// 	// ...
//
// }
#include <iostream>

#include "Windows/AllowWindowsPlatformTypes.h"
#include "WinBase.h"


// Function Description:
// - Sample function which combines the creation of some basic anonymous pipes
//      and passes them to CreatePseudoConsole.
// Arguments:
// - size: The size of the conpty to create, in characters.
// - phInput: Receives the handle to the newly-created anonymous pipe for writing input to the conpty.
// - phOutput: Receives the handle to the newly-created anonymous pipe for reading the output of the conpty.
// - phPty: Receives a token value to identify this conpty
HRESULT CreatePseudoConsoleAndHandles2(COORD size,
									  _In_ DWORD dwFlags,
									  _Out_ HANDLE* phInput,
									  _Out_ HANDLE* phOutput,
									  _Out_ HPCON* phPC)
{
	if (phPC == nullptr || phInput == nullptr || phOutput == nullptr)
	{
		return E_INVALIDARG;
	}

	HANDLE outPipeOurSide;
	HANDLE inPipeOurSide;
	HANDLE outPipePseudoConsoleSide;
	HANDLE inPipePseudoConsoleSide;

	auto hr = S_OK;
	if (!CreatePipe(&inPipePseudoConsoleSide, &inPipeOurSide, nullptr, 0))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
	}
	if (SUCCEEDED(hr))
	{
		if (!CreatePipe(&outPipeOurSide, &outPipePseudoConsoleSide, nullptr, 0))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}
		if (SUCCEEDED(hr))
		{
			hr = CreatePseudoConsole(size, inPipePseudoConsoleSide, outPipePseudoConsoleSide, dwFlags, phPC);
			if (FAILED(hr))
			{
				CloseHandle(inPipeOurSide);
				CloseHandle(outPipeOurSide);
			}
			else
			{
				*phInput = inPipeOurSide;
				*phOutput = outPipeOurSide;
			}
			CloseHandle(outPipePseudoConsoleSide);
		}
		else
		{
			CloseHandle(inPipeOurSide);
		}
		CloseHandle(inPipePseudoConsoleSide);
	}
	return hr;
}

HRESULT AttachPseudoConsole2(HPCON hPC, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList)
{
	BOOL fSuccess = UpdateProcThreadAttribute(lpAttributeList,
											  0,
											  PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE,
											  hPC,
											  sizeof(HPCON),
											  nullptr,
											  nullptr);
	return fSuccess ? S_OK : HRESULT_FROM_WIN32(GetLastError());
}



PRAGMA_DISABLE_OPTIMIZATION

FProcHandle CreateProc(const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden,
                       bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier,
                       const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void* PipeReadChild,
                       void* PipeStdErrChild)
{
	//UE_LOG(LogWindows, Log,  TEXT("CreateProc %s %s"), URL, Parms );

	HANDLE _outPipe = INVALID_HANDLE_VALUE;
	HANDLE _inPipe = INVALID_HANDLE_VALUE;
	HANDLE _signalPipe = INVALID_HANDLE_VALUE;

	HPCON _hPC;

	auto test =  CreatePseudoConsoleAndHandles2({200, 200},  0, &_inPipe, &_outPipe, &_hPC);
	if(FAILED(test))
	{
		;
		
	}

	
	STARTUPINFOEX siEx;
	siEx = { 0 };
	siEx.StartupInfo.cb = sizeof(STARTUPINFOEX);
	size_t size;
	InitializeProcThreadAttributeList(nullptr, 1, 0, (PSIZE_T)&size);
	BYTE* attrList = new BYTE[size];
	siEx.lpAttributeList = reinterpret_cast<PPROC_THREAD_ATTRIBUTE_LIST>(attrList);
	auto fSuccess = InitializeProcThreadAttributeList(siEx.lpAttributeList, 1, 0, (PSIZE_T)&size);
	UpdateProcThreadAttribute(siEx.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE, _hPC, sizeof(_hPC), nullptr, nullptr);


	// AttachPseudoConsole(_hPC, siEx.lpAttributeList);
	// HPCON hPC = SetUpPseudoConsole({200,200});

	// - Close these after CreateProcess of child application with pseudoconsole object.
	HANDLE inputReadSide, outputWriteSide;

	// - Hold onto these and use them for communication with the child through the pseudoconsole.
	HANDLE outputReadSide, inputWriteSide;

	if (!FPlatformProcess::CreatePipe(inputReadSide, inputWriteSide))
	{
		check(0);
	}

	if (!FPlatformProcess::CreatePipe(outputReadSide, outputWriteSide))
	{
		check(0);
	}
	// PipeReadChild = &inputReadSide;


	HPCON hPC;
	HRESULT hr = S_OK;
	hr = CreatePseudoConsole({200,200}, inputReadSide, outputWriteSide, 0, &hPC);
	// HRESULT hr = CreatePseudoConsole({200,200}, nullptr, nullptr, 0, &hPC);

	if(FAILED(hr))
	{
		check(0);

		;
	}


	// initialize process creation flags
	uint32 CreateFlags = CREATE_NO_WINDOW;
	if (PriorityModifier < 0)
	{
		CreateFlags = (PriorityModifier == -1) ? BELOW_NORMAL_PRIORITY_CLASS : IDLE_PRIORITY_CLASS;
	}
	else if (PriorityModifier > 0)
	{
		CreateFlags = (PriorityModifier == 1) ? ABOVE_NORMAL_PRIORITY_CLASS : HIGH_PRIORITY_CLASS;
	}
	
	if (bLaunchDetached)
	{
		CreateFlags |= DETACHED_PROCESS;
	}

	// initialize window flags
	uint32 dwFlags = 0;
	uint16 ShowWindowFlags = SW_HIDE;
	if (bLaunchReallyHidden)
	{
		dwFlags = STARTF_USESHOWWINDOW;
	}
	else if (bLaunchHidden)
	{
		dwFlags = STARTF_USESHOWWINDOW;
		ShowWindowFlags = SW_SHOWMINNOACTIVE;
	}

	if (PipeWriteChild != nullptr || PipeReadChild != nullptr || PipeStdErrChild != nullptr)
	{
		dwFlags |= STARTF_USESTDHANDLES;
	}

	// initialize startup info
	// STARTUPINFO StartupInfo = {
	// 	sizeof(STARTUPINFO),
	// 	NULL, NULL, NULL,
	// 	(::DWORD)CW_USEDEFAULT,
	// 	(::DWORD)CW_USEDEFAULT,
	// 	(::DWORD)CW_USEDEFAULT,
	// 	(::DWORD)CW_USEDEFAULT,
	// 	(::DWORD)0, (::DWORD)0, (::DWORD)0,
	// 	(::DWORD)dwFlags,
	// 	ShowWindowFlags,
	// 	0, NULL,
	// 	HANDLE(PipeReadChild),
	// 	HANDLE(PipeWriteChild),
	// 	HANDLE(PipeStdErrChild)
	// };

	// 创建子进程
	STARTUPINFOEX si;
	ZeroMemory(&si, sizeof(si));
	si.StartupInfo.cb = sizeof(si);

	
	SIZE_T attrListSize;
	InitializeProcThreadAttributeList(nullptr, 1, 0, &attrListSize);
	si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, attrListSize);
	InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, &attrListSize);
	UpdateProcThreadAttribute(si.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE, hPC, sizeof(hPC), nullptr, nullptr);

	// StartupInfo.dwXSize = 100;
	// StartupInfo.dwYSize = 20;
	//
	// StartupInfo.dwFlags =  STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW | STARTF_USECOUNTCHARS;
	// // STARTF_USESTDHANDLES | STARTF_USECOUNTCHARS /*| STARTF_USESIZE */ ;
	// // StartupInfo.dwX = CW_USEDEFAULT;
	// // StartupInfo.dwY = CW_USEDEFAULT;
	// StartupInfo.dwXSize = 100;
	// StartupInfo.dwYSize = 20;
	// StartupInfo.dwXCountChars = 200;
	// StartupInfo.dwYCountChars = 200;
	// //
	// // StartupInfo.wShowWindow = SW_HIDE;
	// //
	// // StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	// StartupInfo.wShowWindow = SW_HIDE;
	

	bool bInheritHandles = (dwFlags & STARTF_USESTDHANDLES) != 0;

	// create the child process
	FString CommandLine = FString::Printf(TEXT("\"%s\" %s"), URL, Parms);
	PROCESS_INFORMATION ProcInfo;

	if (!CreateProcess(NULL, CommandLine.GetCharArray().GetData(), nullptr, nullptr, true, EXTENDED_STARTUPINFO_PRESENT,
	                   NULL, OptionalWorkingDirectory, &siEx.StartupInfo, &ProcInfo))
	{
		DWORD ErrorCode = GetLastError();

		TCHAR ErrorMessage[512];
		FWindowsPlatformMisc::GetSystemErrorMessage(ErrorMessage, 512, ErrorCode);

		UE_LOG(LogWindows, Warning, TEXT("CreateProc failed: %s (0x%08x)"), ErrorMessage, ErrorCode);
		if (ErrorCode == ERROR_NOT_ENOUGH_MEMORY || ErrorCode == ERROR_OUTOFMEMORY)
		{
			// These errors are common enough that we want some available memory information
			FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
			UE_LOG(LogWindows, Warning, TEXT("Mem used: %.2f MB, OS Free %.2f MB"), Stats.UsedPhysical / 1048576.0f, Stats.AvailablePhysical / 1048576.0f);
		}
		UE_LOG(LogWindows, Warning, TEXT("URL: %s %s"), URL, Parms);
		if (OutProcessID != nullptr)
		{
			*OutProcessID = 0;
		}

		return FProcHandle();
	}

	FPlatformProcess::Sleep(1.f); // Sleep for a short time to avoid busy-waiting

	auto Output = FPlatformProcess::ReadPipe(&_outPipe);


	// BYTE buffer[256];
	// DWORD dwRead;
	// while (true)
	// {
	// 	dwRead = 0;
	// 	bool fSuccess1 = false;
	//
	// 	fSuccess1 = !!ReadFile(_outPipe, buffer, ARRAYSIZE(buffer), &dwRead, nullptr);
	// 	if (!fSuccess1)
	// 	{
	// 		HRESULT hr1 = GetLastError();
	// 		exit(hr1);
	// 	}
	//
	// 	std::cout << buffer;
	//
	// }
	
	// 关闭不必要的句柄
	// CloseHandle(pi.hProcess);
	// CloseHandle(pi.hThread);
	// CloseHandle(hPipeInWrite);
	// CloseHandle(hPipeOutRead);

	// 从管道读取子进程的输出

	// char buffer[4096];
	// DWORD bytesRead;
	// while (ReadFile(outputWriteSide, buffer, sizeof(buffer) - 1, &bytesRead, nullptr) && bytesRead > 0)
	// {
	// 	buffer[bytesRead] = '\0';
	// 	std::cout << buffer;
	// }

	if (OutProcessID != nullptr)
	{
		*OutProcessID = ProcInfo.dwProcessId;
	}

	::CloseHandle( ProcInfo.hThread );

	return FProcHandle(ProcInfo.hProcess);
}
PRAGMA_ENABLE_OPTIMIZATION

FProcHandle CreateProc2(const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden, bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier, const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void* PipeReadChild)
{
	// CreateProc used to only have a single "write" pipe argument that both stdout and stderr would be piped into on Windows,
	// so for this overload we'll preserve that behaviour for compatibility with existing code
	return CreateProc(URL, Parms, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, OutProcessID, PriorityModifier, OptionalWorkingDirectory, PipeWriteChild, PipeReadChild, PipeWriteChild);
}

// PRAGMA_DISABLE_OPTIMIZATION

// #include "VtConsole.hpp"

// FString CreateChildProcessAndGetOutput2(const FString& ExecutablePath, const FString& Parameters)
//
// {
// 	
//
//
// 	return FString();
// 	FString CommandLine = ExecutablePath + TEXT(" ") + Parameters;
//
// 	// Create pipes for capturing the output
// 	void* ReadPipe = nullptr;
// 	void* WritePipe = nullptr;
// 	// DWORD bufferSize
// 	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);
//
// 	CONSOLE_SCREEN_BUFFER_INFO info;
//
// 	
// 	// if (!SetNamedPipeHandleState(WritePipe, nullptr, nullptr, &bufferSize))
// 	{
// 		// std::wcerr << L"SetNamedPipeHandleState failed (" << GetLastError() << L").\n";
// 		// CloseHandle(hReadPipe);
// 		// CloseHandle(hWritePipe);
// 		// return;
// 	}
//
// 	// Create the child process
// 	// FProcHandle ProcessHandle = FPlatformProcess::CreateProc(
// 	FProcHandle ProcessHandle = CreateProc2(
// 		*ExecutablePath,     // Path to the executable
// 		*Parameters,         // Command line parameters
// 		true,                // bLaunchDetached
// 		true,                // bLaunchHidden
// 		true,                // bLaunchReallyHidden
// 		nullptr,             // OutProcessID
// 		0,                   // PriorityModifier
// 		nullptr,             // OptionalWorkingDirectory
// 		WritePipe            // PipeWriteChild
// 		,NULL
// 	);
//
// 	GetConsoleScreenBufferInfo(WritePipe, &info);
//
//
// 	Windows::HANDLE ConsoleHandle(WritePipe);
//
// 	// COORD Size(1000,1000);
// 	// SetConsoleScreenBufferSize( ConsoleHandle, Size );
//
//
//
// 	FString Output;
//
// 	if (ProcessHandle.IsValid())
// 	{
// 		// Close the write end of the pipe in the parent process
// 		// FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
//
// 		// Read the output from the child process
// 		// while (FPlatformProcess::IsProcRunning(ProcessHandle))
// 		{
// 			FPlatformProcess::Sleep(2.f); // Sleep for a short time to avoid busy-waiting
// 			FString NewOutput = FPlatformProcess::ReadPipe(ReadPipe);
// 			Output += NewOutput;
// 		}
//
// 		// Read any remaining output
// 		Output += FPlatformProcess::ReadPipe(ReadPipe);
//
// 		// Close the read end of the pipe
// 		FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
// 		// FPlatformProcess::ClosePipe(ReadPipe);
//
// 		// Wait for the process to complete
// 		// FPlatformProcess::WaitForProc(ProcessHandle);
// 		FPlatformProcess::CloseProc(ProcessHandle);
//
// 		UE_LOG(LogTemp, Log, TEXT("Successfully created child process and captured output."));
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Failed to create child process."));
// 	}
//
// 	return Output;
// }
// PRAGMA_ENABLE_OPTIMIZATION
